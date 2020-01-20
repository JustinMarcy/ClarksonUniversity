----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/11/2018 02:25:22 PM
-- Design Name: 
-- Module Name: dbounce - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity dbounce is
	port (
				slow_clk: in STD_LOGIC;
				BTND : in STD_LOGIC;
				BTNR : in STD_LOGIC;
				BTNDdeb : out STD_LOGIC
			);
end dbounce;

architecture behavior of dbounce is
   -- signals that will be used internal to the debounce block
signal Q1, Q2, Q3 : STD_LOGIC;

begin
	 
	--**Insert the following after the 'begin' keyword**
	process(slow_clk)
	begin
	   if (slow_clk'event and slow_clk = '1') then
		  if (BTNR = '1') then
			 Q1 <= '0';
			 Q2 <= '0';
			 Q3 <= '0'; 
		  else
			 Q1 <= BTND;
			 Q2 <= Q1;
			 Q3 <= Q2;
		  end if;
	   end if;
	end process;

	BTNDdeb <= Q1 and Q2 and (not Q3);

end behavior;
