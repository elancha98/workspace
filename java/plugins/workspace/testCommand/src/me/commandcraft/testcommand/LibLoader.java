package me.commandcraft.testcommand;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLClassLoader;
import java.net.URLDecoder;
import java.util.Enumeration;
import java.util.HashSet;
import java.util.Set;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import org.apache.commons.io.IOUtils;
import org.bukkit.Bukkit;
import org.bukkit.configuration.file.YamlConfiguration;
import org.bukkit.plugin.Plugin;

@SuppressWarnings("deprecation")
public class LibLoader {
	
	private static boolean RUNNING_FROM_JAR = false;
	private static String PLUGIN_NAME;
	
	static {
        final URL resource = LibLoader.class.getClassLoader().getResource("plugin.yml");
        if (resource != null) {
        	RUNNING_FROM_JAR = true;
        	try {
				PLUGIN_NAME = YamlConfiguration.loadConfiguration(resource.openStream()).getString("name");
			} catch (IOException e) {
				e.printStackTrace();
			}
        }
    }

	public static void loadLib(String libr) throws Exception {
		Plugin plugin = Bukkit.getPluginManager().getPlugin(PLUGIN_NAME);
		final File lib = new File(plugin.getDataFolder(), libr);
		if (!lib.exists()) extractFromJar(lib.getName(), lib.getAbsolutePath());
		addClassPath(getJarUrl(lib));	
	}
	
	private static void addClassPath(URL url) throws Exception {
		URLClassLoader sysloader = (URLClassLoader) ClassLoader.getSystemClassLoader();
		Class<URLClassLoader> sysclass = URLClassLoader.class;
		Method method = sysclass.getDeclaredMethod("addURL", URL.class);
		method.setAccessible(true);
        method.invoke(sysloader, url);
	}
	
	private static URL getJarUrl(File file) throws MalformedURLException {
		return new URL("jar:" + file.toURI().toURL().toExternalForm() + "!/");
	}
	
	private static boolean extractFromJar(String origin, String destination) throws Exception {
		JarFile jar = getRunningJar();
		if (jar == null) return false;
		File dest = new File(destination);
		if (dest.isDirectory()) return false;
		if (!dest.exists()) dest.getParentFile().mkdirs();
		Enumeration<JarEntry> e = jar.entries();
		while (e.hasMoreElements()) {
			JarEntry jarEntry = (JarEntry) e.nextElement();
			if (!jarEntry.getName().contains(origin)) continue;
			InputStream iStream = new BufferedInputStream(jar.getInputStream(jarEntry));
			OutputStream oStream = new BufferedOutputStream(new FileOutputStream(dest));
			IOUtils.copy(iStream, oStream);
			iStream.close();
			oStream.close();
			jar.close();
			return true;
		}
		jar.close();
		return false;
	}
	
	private static JarFile getRunningJar() throws IOException {
		if (!RUNNING_FROM_JAR) return null;
		String path = new File(LibLoader.class.getProtectionDomain().getCodeSource().
				getLocation().getPath()).getAbsolutePath();
		path = URLDecoder.decode(path, "UTF-8");
		return new JarFile(path);
	}
	
	//Not very related but usefull
	public static Set<Class<?>> getClasses(String packageName) {
        Set<Class<?>> classes = new HashSet<Class<?>>();
        try {
            JarFile file = getRunningJar(); 
            for (Enumeration<JarEntry> entry = file.entries(); entry.hasMoreElements();) { 
               JarEntry jarEntry = entry.nextElement();
               String name = jarEntry.getName().replace("/", ".");
               if(name.startsWith(packageName) && name.endsWith(".class"))
               classes.add(Class.forName(name.substring(0, name.length() - 6)));
            }
            file.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
        return classes;
    }
}
