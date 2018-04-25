package me.commandcraft.lwjgl_demo.kernels;

import me.commandcraft.lwjgl_demo.CLRunner;
import me.commandcraft.lwjgl_demo.Kernel;
import org.lwjgl.opencl.CLMem;

import java.nio.FloatBuffer;

/**
 * Created by ernesto on 14/06/17.
 */
public class SumKernel extends Kernel {

    private int size;
    private CLMem a, b, result;

    public SumKernel(int size) {
        super("SumKernel");
        this.size = size;
        result = CLRunner.alocateReadOnly(size);
    }

    public void setA(float[] data) {
        a = CLRunner.writeToMemory(data);
    }

    public void setB(float[] data) {
        b = CLRunner.writeToMemory(data);
    }

    @Override
    public float[] getResult() {
        float[] ret = new float[size];
        FloatBuffer buffer = CLRunner.getBack(result, size);
        buffer.get(ret);
        return ret;
    }

    @Override
    public void setArgs() {
        kernel.setArg(0, a);
        kernel.setArg(1, b);
        kernel.setArg(2, result);
        kernel.setArg(3, size);
    }

    @Override
    public int getDimension() {
        return 1;
    }

    @Override
    public int getGlobalSize() {
        return size;
    }
}
