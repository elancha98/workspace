package me.commandcraft.soulbound;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.UUID;
import java.util.function.Consumer;

import org.bukkit.entity.Player;
import org.bukkit.event.EventHandler;
import org.bukkit.event.Listener;
import org.bukkit.event.entity.PlayerDeathEvent;
import org.bukkit.event.player.PlayerRespawnEvent;
import org.bukkit.inventory.ItemStack;

public class DeathListener implements Listener {
	
	Map<UUID, ItemStack[]> died = new HashMap<UUID, ItemStack[]>();

	@EventHandler
	public void onEntityDeath(PlayerRespawnEvent event) {
		Player player = event.getPlayer();
		if (died.containsKey(player.getUniqueId())) {
			ItemStack[] items = died.remove(player.getUniqueId());
			player.getInventory().addItem(items);
		}
	}
	
	@EventHandler
	public void onPlayerDeath(PlayerDeathEvent event) {
		Player player = event.getEntity();
		List<ItemStack> keep = new ArrayList<ItemStack>();
		player.getInventory().forEach(new Consumer<ItemStack>() {

			@Override
			public void accept(ItemStack t) {
				if (Utils.isSoulbound(t)) {
					keep.add(t);
					event.getDrops().remove(t);
				}
			}
			
		});
		died.put(player.getUniqueId(), keep.toArray(new ItemStack[0]));
	}
}
