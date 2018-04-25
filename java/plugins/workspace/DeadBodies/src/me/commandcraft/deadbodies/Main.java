package me.commandcraft.deadbodies;

import org.bukkit.Bukkit;
import org.bukkit.Material;
import org.bukkit.entity.EntityType;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.player.PlayerJoinEvent;
import org.bukkit.inventory.ItemStack;
import org.bukkit.plugin.java.JavaPlugin;

import net.citizensnpcs.api.CitizensAPI;
import net.citizensnpcs.api.npc.NPC;
import net.citizensnpcs.api.trait.trait.Inventory;

public class Main extends JavaPlugin implements Listener {
	
	NPC npc;
	
	public void onEnable() {
		
		if(getServer().getPluginManager().getPlugin("Citizens") == null || getServer().getPluginManager().getPlugin("Citizens").isEnabled() == false) {
			getLogger().log(java.util.logging.Level.SEVERE, "Citizens 2.0 not found or not enabled");
			getServer().getPluginManager().disablePlugin(this);	
			return;
		}
		
		npc = CitizensAPI.getNPCRegistry().createNPC(EntityType.PLAYER, "fullwall");
		
		Bukkit.getPluginManager().registerEvents(this, this);
	}
	
	@EventHandler
	public void onPlayerJoin(PlayerJoinEvent event) {
		npc.spawn(event.getPlayer().getLocation());
		while (!npc.isSpawned()) {
			Inventory inventory = new Inventory();
			inventory.setContents(new ItemStack[] { new ItemStack(Material.ELYTRA)});
			npc.addTrait(inventory);
		}
	}
}
