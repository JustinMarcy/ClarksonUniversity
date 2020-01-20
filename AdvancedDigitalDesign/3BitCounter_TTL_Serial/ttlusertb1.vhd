----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/06/2018 11:56:55 AM
-- Design Name: 
-- Module Name: testbench - Behavioral
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
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity testbench is
end testbench;

architecture Behavioral of testbench is

signal reset : STD_LOGIC;
signal clk : STD_LOGIC := '0';
signal cnten : STD_LOGIC;
signal EB : STD_LOGIC;
signal TX : STD_LOGIC;
signal CSN : STD_LOGIC;
signal MOSI : STD_LOGIC := '0';
signal SDCLK : STD_LOGIC;


component toplevel is
port( reset : in STD_LOGIC;
           clk : in STD_LOGIC;
           cnten : in STD_LOGIC;
           EB : in STD_LOGIC;
           TX : out STD_LOGIC;
           CSN : out STD_LOGIC;
           MOSI : out STD_LOGIC;
           SDCLK : out STD_LOGIC);
end component;

begin

Inst_toplevel : component toplevel
    port map(
    reset => reset,
    clk => clk,
    cnten => cnten,
    EB => EB,
    TX => TX,
    CSN => CSN,
    MOSI => MOSI,
    SDCLK => SDCLK
    );

clk <= not clk after 8ns;

process
begin

reset <= '1';
cnten <= '0';
EB <= '1';
wait for 200us;

reset <= '0';
cnten <= '1';
wait for 200us;

EB <= '0';
wait for 200us;

cnten<='0';
wait for 200us;
--EB <= '1';
--wait for 200us;

--cnten <= '0';
--wait for 200us;

cnten <= '1';

wait;

end process;

end Behavioral;
