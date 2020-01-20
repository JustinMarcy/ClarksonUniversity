library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity SPI_user_logic is
    Generic (
        Constant cnt_max : integer := 249);
  Port ( 
        clk             : IN STD_LOGIC;
        iData           : IN STD_LOGIC_VECTOR(15 downto 0);
        MOSI,SCK,SSN    : out STD_LOGIC
        );
end SPI_user_logic;

architecture user_logic of SPI_user_logic is

component SPI_master is
    Generic (Constant CntMax : integer:= 249);  -- (125 MHz/500 KHz) - 1 = 249
Port ( clock             : in std_logic; -- board clock
       iData             : in std_logic_vector(7 downto 0); 
       iReset_n          : in std_logic;  
       iEna              : in std_logic;  
       oBusy             : out std_logic;         
       MOSI,SCK,SSN      : out std_logic
      );
end component;

signal data        : STD_LOGIC_VECTOR(7 downto 0);
signal byteSel     : integer range 0 to 10 :=0;
signal sel         : integer range 0 to 17 :=0;
signal MOSI1        : STD_LOGIC;
signal iReset_n     : STD_LOGIC;
signal busy         : STD_LOGIC;
signal clk_en      : STD_LOGIC;
signal ena          : STD_LOGIC := '1';
signal clk_cnt     : integer range 0 to cnt_max;
type state_type is (start, ready, valid, busy_high, done);
signal state       : state_type;
signal count       : integer := 0;
begin 

MOSI <= MOSI1;

--clk_en_instance: process(CLK)
--    begin
--    if rising_edge(CLK) then 
--        if(clk_cnt = CNT_MAX) then --for simulation only, else use cnt_max
--            clk_cnt <= 0;
--            clk_en <= '1';
--        else 
--            clk_cnt <= clk_cnt +1;
--            clk_en <= '0';
--        end if;
--    end if;
--    end process;

MUX1: process(byteSel, iData)
begin
    case byteSel is
        when 0 => data <= X"76";
        when 1 => data <= X"76";
        when 2 => data <= X"76";
        when 3 => data <= X"7A";
        when 4 => data <= X"FF";
        when 5 => data <= X"77";
        when 6 => data <= X"00";
        when 7 => data <= X"0"&iData(15 downto 12);
        when 8 => data <= X"0"&iData(11 downto 8);
        when 9 => data <= X"0"&iData(7 downto 4);
        when 10 => data <= X"0"&iData(3 downto 0);
        when others => data <= X"76";
    end case;
end process;
instance : component SPI_master
port map ( clock => clk,
       iData => data, 
       iReset_n => iReset_n, 
       iEna => ena,
       oBusy => busy,       
       MOSI => MOSI1,
       SCK => SCK,
       SSN => SSN
       );

--Byte Select State Machine (with reset)
process (clk)
begin

    if (rising_edge(clk)) then
    case state is
        when start => 
        if count /= cnt_max then
        count <= count + 1;
        ireset_n <= '0';
        state <= start;
            else 
                ireset_n <= '1';
                state <= ready;
        end if;
      when ready => 
        if busy = '0' then 
            ena <= '1';
            state <= valid;
        end if;
        when valid => 
            if busy = '1' then 
                ena <= '0';
                state <= busy_high;
            end if;
       when busy_high => 
        if busy = '0' then 
        state <= done;
        end if;
        when done => 
            if byteSel < 10 then 
                byteSel <= byteSel + 1;
            else 
                byteSel <= 7;
            end if;
            state <= start;
       when others => null;  
    end case;
    end if;    
end process;

end user_logic;

