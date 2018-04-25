package me.commandcraft.cubestand;

import java.io.File;
import java.io.IOException;
import java.util.List;

import org.bukkit.configuration.file.FileConfiguration;
import org.bukkit.configuration.file.YamlConfiguration;

public class StandManager {
	
	public enum CommandType {
		PLAYER, CONSOLE;
	}
	
	private FileConfiguration config;

	private static StandManager instance;
	
	private StandManager() {}
	
	public static StandManager getInstance() {
		if (instance == null) instance = new StandManager();
		return instance;
	}
	
	public List<String> getCommands(String uuid, CommandType type) {
		return config.getStringList(uuid + "." + type.toString().toLowerCase());
	}
	
	public void addCommand(String uuid, CommandType type, String command) {
		String path = uuid + "." + type.toString().toLowerCase();
		List<String> commands = config.getStringList(path);
		commands.add(command);
		config.set(path, commands);
	}
	
	public void remove(String uuid) {
		config.set(uuid, null);
	}
	
	public void loadFromFile(File folder) {
		config = YamlConfiguration.loadConfiguration(new File(folder, "stands.yml"));
	}
	
	public void saveConfig(File folder) {
		try {
			config.save(new File(folder, "stands.yml"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
