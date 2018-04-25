package me.commandcraft.showcase;

import java.util.LinkedList;
import java.util.Queue;

import org.bukkit.Bukkit;
import org.bukkit.entity.Player;
import org.bukkit.inventory.ItemStack;

public class ShowCaseManager {

	private Queue<ShowCase> showcases;
	
	public ShowCaseManager() {
		showcases = new LinkedList<ShowCase>();
	}
	
	public void showcase(Player p) {
		ItemStack it = p.getInventory().getItemInMainHand();
		ShowCase sc = new ShowCase(it);
		showcases.add(sc);
		Bukkit.getScheduler().scheduleSyncDelayedTask(Main.getPlugin(), new Runnable() {
			
			@Override
			public void run() {
				showcases.remove().remove();
			}
		}, 20*Main.getConfiguration().getTime());
		String tellraw = "tellraw @a [";
		String part1 = "{\"text\":\"" + p.getName() + "\",\"color\":\"green\",\"bold\":true}";
		String part2 = "{\"text\":\" is showcasing this \",\"color\":\"gold\",\"bold\":false}";
		String part3 = "{\"text\":\"[Item]\",\"color\":\"dark_aqua\",\"bold\":true,\"clickEvent\":{\"action\":\"run_command\",\"value\":\"/showcase " + sc.getId() + "\"}}";
		tellraw += part1 + ",";
		tellraw += part2 + ",";
		tellraw += part3 + "]";
		Bukkit.getLogger().info(tellraw);
		Bukkit.getLogger().info("Error: " + tellraw.charAt(259) + tellraw.charAt(260) + tellraw.charAt(261));
		Bukkit.getServer().dispatchCommand(p, tellraw);
	}
	
	public void display(Player p, String id) {
		for (ShowCase s : showcases) {
			if (s.equalsID(id)) {
				s.openInventory(p);
				return;
			}
		}
	}
}
