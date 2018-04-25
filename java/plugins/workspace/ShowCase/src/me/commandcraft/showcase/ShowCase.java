package me.commandcraft.showcase;

import java.util.UUID;

import org.bukkit.Bukkit;
import org.bukkit.ChatColor;
import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.inventory.InventoryClickEvent;
import org.bukkit.event.inventory.InventoryType;
import org.bukkit.inventory.Inventory;
import org.bukkit.inventory.ItemStack;

public class ShowCase implements Listener {

	Inventory inventory;
	String id;
	
	public ShowCase(ItemStack item) {
		inventory = Bukkit.createInventory(null, InventoryType.DROPPER, ChatColor.GREEN + "ShowCase");
		inventory.setItem(4, item);
		id = UUID.randomUUID().toString();
	}
	
	public void openInventory(Player p) {
		p.openInventory(inventory);
	}
	
	public void remove() {
		InventoryClickEvent.getHandlerList().unregister(this);
	}
	
	public String getId() {
		return this.id;
	}
	
	public boolean equalsID(String id) {
		return this.id.equals(id);
	}
	
	@EventHandler
	public void onInventoryClick(InventoryClickEvent event) {
		if (event.getClickedInventory().equals(this)) {
			event.setCancelled(true);
		}
	}
}
