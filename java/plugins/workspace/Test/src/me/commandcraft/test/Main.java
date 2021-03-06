package me.commandcraft.test;

import org.bukkit.Bukkit;
import org.bukkit.Chunk;
import org.bukkit.Material;
import org.bukkit.block.Block;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.world.ChunkPopulateEvent;
import org.bukkit.plugin.java.JavaPlugin;

public class Main extends JavaPlugin implements Listener {

	public void onEnable() {
		Bukkit.getPluginManager().registerEvents(this, this);
	}
	
	
	@EventHandler
	public void onChunkGenerate(ChunkPopulateEvent event) {
		Chunk chunk = event.getChunk();
		int maxY = event.getWorld().getMaxHeight();
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < maxY; y++) {
				for (int z = 0; z < 16; z++) {
					Block block = chunk.getBlock(x, y, z);
					if (block.getType().equals(Material.CHEST)) {
						Bukkit.getLogger().info("Chest at: " + x + " " + y + " " + z);
					}
				}
			}
		}
		Bukkit.getLogger().info("Veamos");
	}
}
