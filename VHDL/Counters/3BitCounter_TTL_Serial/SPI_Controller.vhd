library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SPI_Controller is
Generic (
CONSTANT cnt_max : integer := 312);--400khz effective clk
    Port  (
           iData : in STD_LOGIC_VECTOR(15 downto 0);
           CLK   : in STD_LOGIC;
           RST   : in STD_LOGIC;
           SDCLK : out STD_LOGIC;  --make 250kHz
           MOSI  : out STD_LOGIC;
           CSN   : out STD_LOGIC);
end SPI_Controller;

architecture Behavioral of SPI_Controller is


signal data        : STD_LOGIC_VECTOR(7 downto 0);
signal byteSel     : integer range 0 to 10 :=0;
signal MUX_OUT     : STD_LOGIC_VECTOR(7 downto 0);
signal sel         : integer range 0 to 17 :=0;
signal clk_en      : STD_LOGIC;
signal clk_cnt     : integer range 0 to cnt_max;

begin 
clk_en_instance: process(CLK)
    begin
    if rising_edge(CLK) then 
        if(clk_cnt = CNT_MAX) then --for simulation only, else use cnt_max
            clk_cnt <= 0;
            clk_en <= '1';
        else 
            clk_cnt <= clk_cnt +1;
            clk_en <= '0';
        end if;
    end if;
    end process;


MUX1: process(byteSel, iData)
begin
    case byteSel is
        when 0 => data <= X"76";
        when 1 => data <= X"76";
        when 2 => data <= X"76";
        when 3 => data <= X"77";
        when 4 => data <= X"00";
        when 5 => data <= X"7A";
        when 6 => data <= X"00";
        when 7 => data <= X"0"&iData(15 downto 12);
        when 8 => data <= X"0"&iData(11 downto 8);
        when 9 => data <= X"0"&iData(7 downto 4);
        when 10 => data <= X"0"&iData(3 downto 0);
        when others => data <= X"00";
    end case;
end process;

MUX2 : process (sel, data)
begin
    case sel is 
        when 0  => SDCLK <= '0'; CSN <= '1'; MOSI <='1';
        when 1  => SDCLK <= '0'; CSN <='0'; MOSI <= data(7);
        when 2  => SDCLK <= '1'; CSN <='0'; MOSI <= data(7);
        when 3  => SDCLK <= '0'; CSN <='0'; MOSI <= data(6);
        when 4  => SDCLK <= '1'; CSN <='0'; MOSI <= data(6);
        when 5  => SDCLK <= '0'; CSN <='0'; MOSI <= data(5);
        when 6  => SDCLK <= '1'; CSN <='0'; MOSI <= data(5);
        when 7  => SDCLK <= '0'; CSN <='0'; MOSI <= data(4);
        when 8  => SDCLK <= '1'; CSN <='0'; MOSI <= data(4);
        when 9  => SDCLK <= '0'; CSN <='0'; MOSI <= data(3);
        when 10 => SDCLK <= '1'; CSN <='0'; MOSI <= data(3);
        when 11 => SDCLK <= '0'; CSN <='0'; MOSI <= data(2);
        when 12 => SDCLK <= '1'; CSN <='0'; MOSI <= data(2);
        when 13 => SDCLK <= '0'; CSN <='0'; MOSI <= data(1);
        when 14 => SDCLK <= '1'; CSN <='0'; MOSI <= data(1);
        when 15 => SDCLK <= '0'; CSN <='0'; MOSI <= data(0);
        when 16 => SDCLK <= '1'; CSN <='0'; MOSI <= data(0);
        when 17 => SDCLK <= '0'; CSN <='0'; MOSI <= '1';  
    end case;
end process;

--Byte Select State Machine (with reset)
process (CLK, RST)
begin
    if RST = '1' then
        byteSel <= 0;
    elsif (rising_edge(CLK) and clk_en='1'and sel = 17) then
        if byteSel <10 then
            byteSel <= byteSel + 1;
        else 
            byteSel <= 7;
        end if;
    end if;    
end process;

--Selector State Machine (with reset)
process (CLK, RST)
begin 

    if RST = '1' then
        sel <= 0;
    elsif (rising_edge(CLK) and clk_en='1') then
        if sel < 17 then
            sel <= sel + 1;
        else
            sel <= 0;
        end if;
    end if;

end process;

end Behavioral;


