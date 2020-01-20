
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity univ_bin_counter is
   generic(N: integer := 4);
   port(
      clk, reset				: in std_logic;
      syn_clr, load, en, up: in std_logic;
		clk_en 					: in std_logic := '1';
      d							: in std_logic_vector(N-1 downto 0);
      max_tick, min_tick	: out std_logic;
      q							: out std_logic_vector(N-1 downto 0)
--		iMax						: in unsigned(N-1 downto 0);
--		iMin						: in unsigned(N-1 downto 0)
   );
end univ_bin_counter;

architecture arch of univ_bin_counter is
   signal r_reg				: unsigned(N-1 downto 0);
   signal r_next				: unsigned(N-1 downto 0);
	signal iMax					: unsigned(N-1 downto 0);
	signal iMin					: unsigned(N-1 downto 0)
begin
   -- register
   process(clk,reset)
   begin
      if (reset='1') then
         r_reg <= (others=>'0');
      elsif rising_edge(clk) and clk_en = '1' then
         r_reg <= r_next;
      end if;
   end process;
   -- next-state logic
   r_next <= (others=>'0') when syn_clr='1' else
             unsigned(d)   when load='1' else
             r_reg + 1     when en ='1' and up='1' else
             r_reg - 1     when en ='1' and up='0' else
             r_reg;
   -- output logic
   q <= std_logic_vector(r_reg);
   max_tick <= '1' when r_reg=iMax else '0';
   min_tick <= '1' when r_reg=iMin else '0';
end arch;

