package me.commandcraft.cubestand;

import java.util.List;

import org.bukkit.Bukkit;
import org.bukkit.ChatColor;
import org.bukkit.command.Command;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.ArmorStand;
import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.block.Action;
import org.bukkit.event.player.PlayerInteractEntityEvent;
import org.bukkit.event.player.PlayerInteractEvent;
import org.bukkit.plugin.java.JavaPlugin;

import me.commandcraft.cubestand.StandManager.CommandType;

public class CubeStand extends JavaPlugin implements Listener {
	
	public void onEnable() {
		Bukkit.getPluginManager().registerEvents(this, this);
		StandManager.getInstance().loadFromFile(getDataFolder());
	}
	
	public void onDisable() {
		StandManager.getInstance().saveConfig(getDataFolder());
	}
	
	public boolean onCommand(CommandSender sender, Command cmd, String commandLabel, String[] args) {
		if (cmd.getName().equalsIgnoreCase("mstand")) {
			if (sender instanceof Player) {
				Player p = (Player) sender;
				if (args.length == 0) return false;
				if (args[0].equalsIgnoreCase("remove")) {
					ArmorStand stand = Utils.getArmorStand(p);
					if (stand == null) {
						p.sendMessage(ChatColor.RED + "You are not looking at an armor stand");
						return true;
					}
					StandManager.getInstance().remove(stand.getUniqueId().toString());
					p.sendMessage(ChatColor.YELLOW + "All commands cleared");
				} else if (args[0].equalsIgnoreCase("add")) {
					if (args.length < 3) return false;
					ArmorStand stand = Utils.getArmorStand(p);
					if (stand == null) {
						p.sendMessage(ChatColor.RED + "You are not looking at an armor stand");
						return true;
					}
					String command = "";
					for (int i = 2; i < args.length; i++) {
						command += args[i] + " ";
					}
					CommandType type;
					if (args[1].equalsIgnoreCase("c")) {
						type = CommandType.CONSOLE;
					} else if (args[1].equalsIgnoreCase("p")) {
						type = CommandType.PLAYER;
					} else return false;
					StandManager.getInstance().addCommand(stand.getUniqueId().toString(), type, command);
					p.sendMessage(ChatColor.GREEN + "added command!");
				}
			} else {
				sender.sendMessage(ChatColor.RED + "Command only usable by players");
			}
		}
		return true;
	}
	
	@EventHandler
	public void onPlayerClickEntity(PlayerInteractEntityEvent event) {
		Bukkit.getLogger().info("ATPC");
	}
	
	@EventHandler(ignoreCancelled=true)
	public void onPlayerClick(PlayerInteractEvent event) {
		Bukkit.getLogger().info("registered");
		if (event.getAction() == Action.RIGHT_CLICK_AIR || event.getAction() == Action.RIGHT_CLICK_BLOCK) {
			ArmorStand stand = Utils.getArmorStand(event.getPlayer());
			if (stand == null) return;
			String uuid = stand.getUniqueId().toString();
			List<String> ccommands = StandManager.getInstance().getCommands(uuid, CommandType.CONSOLE);
			List<String> pcommands = StandManager.getInstance().getCommands(uuid, CommandType.PLAYER);
			for (String cmd : ccommands) {
				Bukkit.getServer().dispatchCommand(Bukkit.getConsoleSender(), cmd);
			}
			for (String cmd : pcommands) {
				Bukkit.getServer().dispatchCommand(event.getPlayer(), cmd);
			}
		}
	}
}
