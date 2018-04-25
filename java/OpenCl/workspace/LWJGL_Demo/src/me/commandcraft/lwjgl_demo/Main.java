package me.commandcraft.lwjgl_demo;

import me.commandcraft.lwjgl_demo.kernels.ProdKernel;
import me.commandcraft.lwjgl_demo.kernels.SumKernel;
import org.lwjgl.LWJGLException;

public class Main {

    public static void main(String[] args) {
        try {
            CLRunner.init();
        } catch (LWJGLException e) {
            e.printStackTrace();
            System.exit(-1);
        }

        SumKernel kernel = new SumKernel(2);
        float[] test = new float[2];
        for (int i = 0; i < test.length; i++)
            test[i] = i;

        kernel.setA(test);
        kernel.setB(test);
        kernel.compile();

        kernel.run();

        float[] res = kernel.getResult();
        for (int i = 0; i < res.length; i++)
            System.out.println(res[i]);

        CLRunner.cleanUp();
    }
}