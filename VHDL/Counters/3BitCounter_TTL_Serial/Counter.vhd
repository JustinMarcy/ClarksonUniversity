library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith;
use IEEE.std_logic_unsigned;

entity counter is 
generic (
constant cntmax : std_logic_vector(3 downto 0) := X"9";--what the counter counts up to
constant divider : integer := 1125000000);--clk/divider is the counter frequency. 125000000 is the zybo z7 board clock.
port (  reset  : in std_logic; -- if 1, resets count btno
	cnten  : in std_logic; -- if 0, does not count. if 1 does count toggle
	eb     : in std_logic; -- if 1, counts up. if 0, counts down toggle inout because being switched inside of code
	clkc    : in std_logic;
	data_O : out std_logic_vector(3 downto 0));
end counter;

architecture behavioral of counter is 

signal counter : integer := 0;
signal count : std_logic_vector(3 downto 0) := (others => '0');

begin

process(clkc)

begin
if (rising_edge(clkc)) then
if (cnten ='1') then
	if (reset = '1') then
		count <= (others => '0');
	elsif (reset = '0') then
	        if (eb = '1') then
	        counter <= counter +1;
	            if (counter = divider) then
	               counter <= 0;
	               if (count < cntmax) then
	                   count <= count + 1;
	               elsif (count = cntmax) then
	                   count <= (others => '0');
	               end if;
	            end if;
	        elsif (eb = '0') then
	        counter <= counter + 1;
	            if (counter = divider) then 
	               counter <= 0;
	               if (count > 0) then
	                   count <= count-1;
	               elsif (count = 0) then
	                   count <= count + 1;
	                   count <= cntmax;
	               end if;
	            end if;
	        end if;
    end if; 
    end if;
elsif(cnten = '0') then
end if;

end process;

data_O <= count;

end behavioral;