package me.commandcraft.parkshooter;

import java.util.List;

import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Entity;
import org.bukkit.plugin.java.JavaPlugin;

import me.commandcraft.parkshooter.commands.CommandExec;

public class ParkShooter extends JavaPlugin {

	public void onEnable() {
		//TODO register commands
		//TODO open config
		try {
			CommandExec.setWrapper();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	public void onDisable() {
		//TODO save config
	}
	
	public boolean onCommand(CommandSender sender, Command cmd, String label, String[] args) {
		List<Entity> list = CommandExec.getEntities(sender, args[0]);
		sender.sendMessage("Length: " + list.size());
		return false;
	}
}
