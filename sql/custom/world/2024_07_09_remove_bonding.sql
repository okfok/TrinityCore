UPDATE world.item_template
SET `bonding` = 0
WHERE `bonding` = 1
   or `bonding` = 2
   or `bonding` = 3;