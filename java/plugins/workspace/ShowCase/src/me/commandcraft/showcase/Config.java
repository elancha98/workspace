package me.commandcraft.showcase;

import java.io.File;
import java.io.IOException;

import org.bukkit.Bukkit;
import org.bukkit.ChatColor;
import org.bukkit.configuration.file.FileConfiguration;
import org.bukkit.configuration.file.YamlConfiguration;

public class Config {

	FileConfiguration config;
	
	public Config(File folder) {
		config = YamlConfiguration.loadConfiguration(new File(folder, "config.yml"));
	}
	
	public void save(File folder) {
		try {
			config.save(new File(folder, "config.yml"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public int getTime() {
		if (!config.contains("showcase_time")) {
			config.set("showcase_time", 20);
			Bukkit.getLogger().severe(ChatColor.RED + "[ShowCase] You don't have \"showcase_time\" set in config.yml");
		}
		return config.getInt("showcase_time");
	}
}
