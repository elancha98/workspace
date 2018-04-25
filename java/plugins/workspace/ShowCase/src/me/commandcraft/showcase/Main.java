package me.commandcraft.showcase;

import org.bukkit.ChatColor;
import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Player;
import org.bukkit.plugin.java.JavaPlugin;

public class Main extends JavaPlugin {
	
	private static Main instance;
	private static Config config;
	
	private ShowCaseManager manager;

	public void onEnable() {
		instance = this;
		config = new Config(getDataFolder());
		manager = new ShowCaseManager();
	}
	
	public void onDisable() {
		config.save(getDataFolder());
	}
	
	public boolean onCommand(CommandSender sender, Command cmd, String useless, String[] args) {
		if (sender instanceof Player) {
			Player player = (Player) sender;
			if (args.length == 0) manager.showcase(player);
			else {
				manager.display(player, args[0]);
			}
			
		} else sender.sendMessage(ChatColor.RED + "command only usable by players");
		return true;
	}
	
	public static Main getPlugin() {
		return instance;
	}
	
	public static Config getConfiguration() {
		return config;
	}
}
