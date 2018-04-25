package me.commandcraft.parkshooter;

import org.bukkit.Bukkit;
import org.bukkit.ChatColor;
import org.bukkit.plugin.java.JavaPlugin;

public class Logger {
	
	private static String PLUGIN;
	
	public static void init(JavaPlugin plugin) {
		PLUGIN = "[" + plugin.getDescription().getName() + "] ";
	}

	public static void info(String msg) {
		Bukkit.getLogger().info(PLUGIN + msg);
	}
	
	public static void severe(String msg) {
		Bukkit.getLogger().severe(ChatColor.RED + PLUGIN + msg);
	}
}
