package me.commandcraft.lwjgl_demo;

import org.lwjgl.BufferUtils;
import org.lwjgl.LWJGLException;
import org.lwjgl.PointerBuffer;
import org.lwjgl.opencl.*;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class CLRunner {

    private static CLPlatform platform;
    private static List<CLDevice> devices;
    private static CLContext context;
    private static CLCommandQueue queue;

    private static List<CLMem> memory;
    private static List<CLProgram> programs;
    private static List<CLKernel> kernels;

    private static IntBuffer errorBuff = BufferUtils.createIntBuffer(1);

    public static void init() throws LWJGLException {
        CL.create();
        platform = CLPlatform.getPlatforms().get(0);
        devices = platform.getDevices(CL10.CL_DEVICE_TYPE_GPU);
        context = CLContext.create(platform, devices, errorBuff);
        queue = CL10.clCreateCommandQueue(context, devices.get(0), CL10.CL_QUEUE_PROFILING_ENABLE, errorBuff);
        Util.checkCLError(errorBuff.get(0));
        memory = new ArrayList<CLMem>();
        programs = new ArrayList<CLProgram>();
        kernels = new ArrayList<CLKernel>();
    }

    public static CLKernel createKernel(String source, String main_name) {
        CLProgram program = CL10.clCreateProgramWithSource(context, source, errorBuff);
        programs.add(program);
        int error = CL10.clBuildProgram(program, devices.get(0), "", null);

        CLKernel kernel = CL10.clCreateKernel(program, main_name, errorBuff);
        kernels.add(kernel);

        Util.checkCLError(errorBuff.get(0));
        Util.checkCLError(error);
        return kernel;
    }

    public static void run(Kernel k) {
        final int dimensions = k.getDimension();
        PointerBuffer globalWorkSize = BufferUtils.createPointerBuffer(dimensions);
        globalWorkSize.put(0, k.getGlobalSize());

        //clEnqueueNDRangleKernel() creates and runs our kernel.
        //The first argument, 'queue' is a CLCommandQueue which must be created for the same device we made our program for.
        //Second, 'sumKernel' is the CLKernel that we want to run.
        //Third, 'dimensions' is an integer specifying the number of dimensions of our work.
        //Fourth, null value MUST ALWAYS BE NULL. It is there because the good people at Khronos are thinking ahead like expert programmers, but it has no use in OpenCL at the moment.
        //Fifth, 'globalWorkSize' has already been explained.
        //Sixth, the null localWorkSize argument is not necessary but I will explain it in a moment.
        //The seventh and eighth null values are for queuing events and are not necessary.
        CL10.clEnqueueNDRangeKernel(queue, k.getKernel(), dimensions, null, globalWorkSize, null, null, null);

        CL10.clFinish(queue);
    }

    public static FloatBuffer getBack(CLMem mem, int size) {
        FloatBuffer writeTo = BufferUtils.createFloatBuffer(size);
        CL10.clEnqueueReadBuffer(queue, mem, CL10.CL_TRUE, 0, writeTo, null, null);
        CL10.clFinish(queue);
        return writeTo;
    }

    //@param size indicates number of floats
    public static CLMem alocateReadOnly(int size) {
        CLMem mem = CL10.clCreateBuffer(context, CL10.CL_MEM_READ_ONLY, size*4, errorBuff);
        Util.checkCLError(errorBuff.get(0));
        memory.add(mem);
        return mem;
    }

    public static CLMem writeToMemory(float[] dataArray) {
        FloatBuffer dataBuff = BufferUtils.createFloatBuffer(dataArray.length*4);
        dataBuff.put(dataArray);
        dataBuff.rewind();
        CLMem mem = CL10.clCreateBuffer(context, CL10.CL_MEM_WRITE_ONLY | CL10.CL_MEM_COPY_HOST_PTR,
                dataBuff, errorBuff);
        Util.checkCLError(errorBuff.get(0));
        memory.add(mem);
        return mem;
    }

    public static void cleanUp() {
        for (CLKernel kernel : kernels) {
            CL10.clReleaseKernel(kernel);
        }
        for (CLProgram program : programs) {
            CL10.clReleaseProgram(program);
        }
        for (CLMem mem : memory) {
            CL10.clReleaseMemObject(mem);
        }
        CL10.clReleaseCommandQueue(queue);
        CL10.clReleaseContext(context);
        CL.destroy();
    }
}
