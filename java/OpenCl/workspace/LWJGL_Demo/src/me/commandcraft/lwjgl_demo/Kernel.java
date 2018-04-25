package me.commandcraft.lwjgl_demo;

import org.lwjgl.BufferUtils;
import org.lwjgl.opencl.*;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.IntBuffer;

/**
 * Created by ernesto on 14/06/17.
 */
public abstract class Kernel {

    private final String fileName;
    private String source;
    protected CLKernel kernel;

    private boolean compiled = false;


    protected Kernel(String fileName) {
        this.fileName = fileName;
        reload();
    }

    public void compile() {
        kernel = CLRunner.createKernel(source, fileName);
        compiled = true;
    }

    public abstract void setArgs();

    public void run() {
        if (!compiled)
            compile();
        setArgs();
        CLRunner.run(this);
    }

    public abstract float[] getResult();

    public abstract int getDimension();

    public abstract int getGlobalSize();

    public CLKernel getKernel() {
        return kernel;
    }

    public void reload() {
        String file = this.getClass().getPackage().getName().replace('.', '/');
        file += "/" + fileName;
        if(!file.endsWith(".cls")) {
            file += ".cls";
        }
        BufferedReader br = null;
        String resultString = null;
        try {
            // Get the file containing the OpenCL kernel source code
            File clSourceFile = new File(this.getClass().getClassLoader().getResource(file).toURI());
            // Create a buffered file reader to read the source file
            br = new BufferedReader(new FileReader(clSourceFile));
            // Read the file's source code line by line and store it in a string buffer
            String line = null;
            StringBuilder result = new StringBuilder();
            while((line = br.readLine()) != null) {
                result.append(line);
                result.append("\n");
            }
            // Convert the string builder into a string containing the source code to return
            resultString = result.toString();
        } catch(NullPointerException npe) {
            // If there is an error finding the file
            System.err.println("Error retrieving OpenCL source file: ");
            npe.printStackTrace();
        } catch(URISyntaxException urie) {
            // If there is an error converting the file name into a URI
            System.err.println("Error converting file name into URI: ");
            urie.printStackTrace();
        } catch(IOException ioe) {
            // If there is an IO error while reading the file
            System.err.println("Error reading OpenCL source file: ");
            ioe.printStackTrace();
        } finally {
            // Finally clean up any open resources
            try {
                br.close();
            } catch (IOException ex) {
                // If there is an error closing the file after we are done with it
                System.err.println("Error closing OpenCL source file");
                ex.printStackTrace();
            }
        }

        // Return the string read from the OpenCL kernel source code file
        source = resultString;
    }
}
