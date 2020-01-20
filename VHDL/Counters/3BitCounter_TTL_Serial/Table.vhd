----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/04/2018 03:48:50 PM
-- Design Name: 
-- Module Name: Table - Behavioral
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
use IEEE.NUMERIC_STD.ALL;
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Table is
    Port ( datain : in STD_LOGIC_Vector(3 downto 0);
           hexn : out STD_LOGIC_VECTOR(15 downto 0));
end Table;

architecture Behavioral of Table is

begin

    process(datain)
    begin
    case datain is
    when X"0" => hexn <= X"0000";
    when X"1" => hexn <= X"CAFE";
    when X"2" => hexn <= X"FADE";
    when X"3" => hexn <= X"4B1D";
    when X"4" => hexn <= X"DEAD";
    when X"5" => hexn <= X"BEEF";
    when X"6" => hexn <= X"FEED";
    when X"7" => hexn <= X"1BAD";
    when X"8" => hexn <= X"D00D";
    when X"9" => hexn <= X"F00D";
    when others => hexn <= X"0000";
    end case;
    end process;

end Behavioral;
