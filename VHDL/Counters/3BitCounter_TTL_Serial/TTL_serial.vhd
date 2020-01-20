library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity TTL_serial is
    GENERIC (
        CONSTANT cnt_max : integer := 13021);
        Port ( clk     : in STD_LOGIC;
               reset_n : in STD_LOGIC;
               ena     : in STD_LOGIC;
               idata   : in STD_LOGIC_VECTOR(7 downto 0);
               busy    : out STD_LOGIC;
               TX      : out STD_LOGIC);
end TTL_serial;

architecture state_machine of TTL_serial is
type stateType is (ready, Start, Send, Stop);
signal state    : stateType;
signal bit_cnt  : integer;
signal data     : std_logic_vector(7 downto 0);
signal clk_cnt  : integer range 0 to cnt_max;
signal clk_en   : std_logic;

begin
clk_en_inst: process(clk)
    begin
    if rising_edge(clk) then 
        if(clk_cnt = cnt_max) then --for simulation only, else use cnt_max
            clk_cnt <= 0;
            clk_en <= '1';
        else 
            clk_cnt <= clk_cnt +1;
            clk_en <= '0';
        end if;
    end if;
    end process;
    
    process(clk, reset_n, clk_en)
    begin
        if reset_n = '0' then 
        state <= ready;
        busy <= '1';
        bit_cnt <= 0;
        TX <= '1'; --Dont need if output is pulled high
        
       elsif rising_edge(clk) and clk_en = '1' then 
       
       case state is 
            when ready =>              --READY
                if ena = '0' then
                    busy <= '0';
                    state <= ready;
                else
                    busy <= '1';
                    data <= idata;
                    state <= start;
                    TX <= '0';
                end if;
            when start =>              --START
                TX <= data(bit_cnt);
                state <= Send;
            when Send =>               --SEND
                if bit_cnt <7 then 
                    TX <= data(bit_cnt + 1);
                    bit_cnt <= bit_cnt + 1;
                    state <= Send;
                else 
                    state <= Stop;
                    bit_cnt <= 0;
                    TX <= '1';
                end if;
            when Stop =>                --STOP
                state <= ready;
                busy <= '0';
            end case;
        end if;
   end process;
end state_machine;   