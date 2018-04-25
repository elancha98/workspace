package me.commandcraft.lwjgl_demo.kernels;

import me.commandcraft.lwjgl_demo.CLRunner;
import me.commandcraft.lwjgl_demo.Kernel;
import org.lwjgl.opencl.CLMem;

import java.nio.FloatBuffer;

/**
 * Created by ernesto on 16/06/17.
 */
public class ProdKernel extends Kernel {

    private CLMem a, b, result;
    private int size;

    public ProdKernel(int size) {
        super("ProdKernel");
        this.size = size;
        result = CLRunner.alocateReadOnly(1);
    }

    public void setA(float[] data) {
        a = CLRunner.writeToMemory(data);
    }

    public void setB(float[] data) {
        b = CLRunner.writeToMemory(data);
    }

    @Override
    public void setArgs() {
        kernel.setArg(0, a);
        kernel.setArg(1, b);
        kernel.setArg(2, result);
        kernel.setArg(3, size);
    }

    @Override
    public float[] getResult() {
        float[] ret = new float[1];
        FloatBuffer buffer = CLRunner.getBack(result, 1);
        buffer.get(ret);
        return ret;
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
