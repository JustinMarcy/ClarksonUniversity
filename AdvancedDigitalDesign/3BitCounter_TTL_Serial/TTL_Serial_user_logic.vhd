library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity TTL_Serial_user_logic is
GENERIC(
CONSTANT cnt_max : integer := 13021);
    Port ( clk   : in STD_LOGIC;
           idata : in STD_LOGIC_VECTOR(15 downto 0);
           TX    : out STD_LOGIC);
end TTL_Serial_user_logic;

architecture user_logic of TTL_Serial_user_logic is
type state_type is(start, ready, data_valid, busy_high, repeat);
signal state       : state_type;
signal reset_n     : STD_LOGIC;
signal ena         : STD_LOGIC;
signal data        : STD_LOGIC_VECTOR(7 downto 0);
signal data_wr     : STD_LOGIC_VECTOR(7 downto 0);
signal busy        : STD_LOGIC;
signal busy_prev   : STD_LOGIC;
signal count       : integer := 13021; --note
signal byteSel     : integer range 0 to 10 :=0;
signal sig_TX      : std_logic;

Component TTL_Serial is
    GENERIC (
    CONSTANT cnt_max : integer := 13021);
    Port ( clk     : in STD_LOGIC;
           reset_n : in STD_LOGIC;
           ena     : in STD_LOGIC;
           idata   : in STD_LOGIC_VECTOR(7 downto 0);
           busy    : out STD_LOGIC;
           TX      : out STD_LOGIC);
end Component;

begin
    TX <= sig_TX;
    
    process(byteSel, iData)
    begin
    case byteSel is
    when 0 => data <= X"76";
    when 1 => data <= X"76";
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
    
    Inst_TTL_Serial: TTL_Serial 
        port map(
            clk => clk,
            reset_n => reset_n,
            ena => ena,
            idata => data,
            busy => busy,
            TX => sig_TX
        );
    
    
    
    
    
    
    process(clk)
    begin
    if(clk'event and clk ='1') then
    case state is
    when start =>
    if count /= 0 then
    count <= count-1;
    reset_n <= '0';
    state <= start;
    ena <= '0';
    else
    reset_n <= '1';
    state <= ready;
    data_wr <= data;
    end if;
    when ready =>
    if busy = '0' then
    ena <= '1';
    state <= data_valid;
    end if;
    when data_valid =>
    if busy = '1' then
    ena <= '0';
    state <= busy_high;
    end if;
    when busy_high => 
    if(busy = '0') then
    state <= repeat;
    end if;
    when repeat =>
    if byteSel <10 then
    byteSel <= byteSel + 1;
    else byteSel <= 7;
    end if;
    state <= start;
    when others => null;
    end case;
    end if;
    end process;
    

end user_logic;
