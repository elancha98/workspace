package me.commandcraft.chestbank;

import java.io.File;
import java.io.IOException;

import org.bukkit.ChatColor;
import org.bukkit.configuration.file.YamlConfiguration;

public class Configuration {

	private YamlConfiguration config;
	
	public Configuration() {
		load();
	}
	
	public String getTitle() {
		String title = config.getString("bank_title");
		if (title == null) {
			config.set("bank_title", "&eChestBank");
			title = "&eChestBank";
		}
		return ChatColor.translateAlternateColorCodes('&', title);
	}
	
	public void load() {
		File file = new File(ChestBank.getInstance().getDataFolder(), "config.yml");
		config = YamlConfiguration.loadConfiguration(file);
	}
	
	public void save() throws IOException {
		File file = new File(ChestBank.getInstance().getDataFolder(), "config.yml");
		if (!file.exists()) file.createNewFile();
		config.save(file);;
	}
}
