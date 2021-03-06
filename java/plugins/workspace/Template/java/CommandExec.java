package me.commandcraft.testcommand;

import java.lang.reflect.Method;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.UUID;

import org.bukkit.Bukkit;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.plugin.java.JavaPlugin;

import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;

public class CommandExec {

	private static final String[] libs = {"asm-5.2.jar", "cglib-3.2.5.jar"};
	private static Object wrapper;
	@SuppressWarnings("rawtypes")
	private static Map<String, List> entities = new HashMap<String, List>();
	
	static {
		try {
			for (String lib : libs) LibLoader.loadLib(lib);
			setWrapper();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	@SuppressWarnings("rawtypes")
	public static List getEntities(CommandSender sender, String selector)  {
		String uuid = UUID.randomUUID().toString();
		try {
			wrapper.getClass().getMethod("execute", CommandSender.class, String[].class)
				.invoke(wrapper, sender, new String[] {selector, uuid});
		} catch (Exception e) {
			return Collections.emptyList();
		}
		return entities.remove(uuid);
	}
	
	public static void setCommands(JavaPlugin plugin) throws Exception {
		Set<Class<?>> classes = LibLoader.getClasses(CommandExec.class.getPackage().getName() + ".commands");
		for (Class<?> clazz : classes) {
			if (CommandExecutor.class.isAssignableFrom(clazz)) {
				String[] cmds = (String[]) clazz.getField("COMMANDS").get(null);
				for (String cmd : cmds) {
					plugin.getCommand(cmd).setExecutor((CommandExecutor) clazz.newInstance());
				}
			}
		}
	}
	
	private static void setWrapper() throws Exception {
		String version = Bukkit.getServer().getClass().getPackage().getName().split("\\.")[3];
		Class<?> vanilla = Class.forName("org.bukkit.craftbukkit." + version + ".command.VanillaCommandWrapper");
		Class<?> cmdabs = Class.forName("net.minecraft.server." + version + ".CommandAbstract");
		
		Class<?> enhancer = Class.forName("net.sf.cglib.proxy.Enhancer");
		Class<?> callback = Class.forName("net.sf.cglib.proxy.Callback");
		Object e = enhancer.getMethod("create", Class.class, callback).invoke(null, cmdabs, new Interceptor(version));
		wrapper = vanilla.getConstructor(cmdabs).newInstance(e);
		if (wrapper == null) throw new Exception("Cannot instanciate VanillaCommandWrapper");
	}
	
	protected static void putEntities(String uuid, @SuppressWarnings("rawtypes") List list) {
		entities.put(uuid, list);
	}
}

class Interceptor implements MethodInterceptor {
	
	private Method get_players;
	private Class<?> entity;
	
	protected Interceptor(String version) throws ClassNotFoundException {
		entity = Class.forName("net.minecraft.server." + version + ".Entity");
		Class<?> selector = Class.forName("net.minecraft.server." + version + ".PlayerSelector");
		Method[] methods = selector.getDeclaredMethods();
		for (Method method : methods) {
			if (method.getName().equals("getPlayers")) get_players = method;
		}		
	}
	
	@SuppressWarnings("rawtypes")
	@Override
	public Object intercept(Object t, Method method, Object[] args, MethodProxy proxy) throws Throwable {
		String name = method.getName();
		if (name.equals("compareTo")) return 0;
		if (name.equals("getUsage")) return null;
		if (name.equals("getCommand")) return null;
		if (name.equals("execute")) {
			List list = (List) get_players.invoke(null, args[0], ((String[]) args[1])[0], entity);
			CommandExec.putEntities(((String[]) args[1])[1], list);
			return null;
		}
		return proxy.invokeSuper(t, args);
	}
}
