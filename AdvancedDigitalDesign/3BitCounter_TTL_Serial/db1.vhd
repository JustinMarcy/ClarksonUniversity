----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/04/2018 03:51:04 PM
-- Design Name: 
-- Module Name: db3 - Behavioral
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
use IEEE.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity db1 is
  GENERIC (
  CONSTANT CNTR_MAX : std_logic_vector(15 downto 0) := X"0009");  
  Port ( BTN_I1     : in  STD_LOGIC;
         CLK1         : in  STD_LOGIC;
         BTN_O1     : out  STD_LOGIC;
         TOGGLE_O1 : out  STD_LOGIC);
end db1;

architecture Behavioral of db1 is
signal btn_cntr   : std_logic_vector(15 downto 0) := (others => '0');
signal btn_reg    : std_logic   				  := '0';
signal btn_toggle : std_logic                     := '1';
signal btn_sync   : std_logic_vector(1 downto 0)  := (others => '0');
signal btn_pulse  : std_logic                     := '0';
begin

	btn_debounce_process : process (CLK1)
	begin
		if (rising_edge(CLK1)) then
			if (btn_cntr = CNTR_MAX) then
				btn_reg <= not(btn_reg);
			end if;
		end if;
	end process;
	
	btn_counter_process : process (CLK1)
	begin
		if (rising_edge(CLK1)) then
			if ((btn_reg = '1') xor (BTN_I1 = '1')) then
				if (btn_cntr = CNTR_MAX) then
					btn_cntr <= (others => '0');
				else
				    btn_cntr <= btn_cntr + 1;
				end if;
			else
				btn_cntr <= (others => '0');
			end if;
		end if;
	end process;
	
	btn_toggle_process : process(CLK1)
	begin
		if (rising_edge(CLK1)) then
			btn_sync(0) <= btn_reg;
			btn_sync(1) <= btn_sync(0);
			btn_pulse   <= not btn_sync(1) and btn_sync(0);	
				if 	btn_pulse = '1' then
					btn_toggle <= not btn_toggle;
				end if;
		end if;
	end process;
					  
	BTN_O1 <= btn_reg;
	TOGGLE_O1 <= btn_toggle;

end Behavioral;
