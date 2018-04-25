package me.commandcraft.chestbank;

import org.bukkit.ChatColor;
import org.bukkit.Location;
import org.bukkit.Material;
import org.bukkit.command.Command;
import org.bukkit.command.CommandExecutor;
import org.bukkit.command.CommandSender;
import org.bukkit.entity.Player;

public class CommandExec implements CommandExecutor {

	@Override
	public boolean onCommand(CommandSender sender, Command cmd, String label, String[] args) {
		if (args.length < 2) {
			usage(sender);
			return false;
		}
		if (args[0].equals("set")) {
			if (!sender.hasPermission("chestbank.set")) {
				sender.sendMessage(ChatColor.RED + "You don't have permission to use that command");
				return false;
			}
			int rows;
			try {
				rows = Integer.parseInt(args[2]);
			} catch (Exception e) {
				sender.sendMessage(ChatColor.RED + "Invalid number of rows");
				return false;
			}
			if (ChestBank.getBankManager().setBank(args[1], rows))
					sender.sendMessage(ChatColor.GREEN + args[1] + " space set to " + rows + " rows.");
			else sender.sendMessage(ChatColor.RED + "Cannot resize bank to smaller number of rows");
		} else if (args[0].equals("add")) {
			if (!sender.hasPermission("chestbank.add")) {
				sender.sendMessage(ChatColor.RED + "You don't have permission to use that command");
				return false;
			}
			if (!(sender instanceof Player)) {
				sender.sendMessage(ChatColor.RED + "Command only usable by players");
				return false;
			}
			Player p = (Player) sender;
			if (ChestBank.getBankManager().hasBank(args[1])) {
				Location loc = Utils.getTarget(p);
				if (loc.getBlock().getType().equals(Material.CHEST) || loc
						.getBlock().getType().equals(Material.TRAPPED_CHEST)) {
					p.sendMessage(ChatColor.RED + "That's not a chest");
					return false;
				}
				if (ChestBank.getBankManager().hasLocation(loc)) {
					p.sendMessage(ChatColor.RED + "That's already a bank");
					return false;
				}
				ChestBank.getBankManager().addLocation(args[1], loc);
				sender.sendMessage(ChatColor.GREEN + "Chest added");
			} else {
				sender.sendMessage(ChatColor.RED + "You have to set rows first");
			}
		} else {
			usage(sender);
		}
		return false;
	}
	
	public void usage(CommandSender sender) {
		sender.sendMessage(ChatColor.RED + "usage:");
		sender.sendMessage(ChatColor.RED + "/chestbank set <group> <rows>");
		sender.sendMessage(ChatColor.RED + "/chestbank add <group>");
	}
}
