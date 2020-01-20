----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 11/04/2018 04:29:10 PM
-- Design Name: 
-- Module Name: toplevel - Behavioral
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

entity toplevel is
    Port ( reset : in STD_LOGIC;
           clk : in STD_LOGIC;
           cnten : in STD_LOGIC;
           EB : in STD_LOGIC;
           TX : out STD_LOGIC;
           SDCLK : out STD_LOGIC;
           MOSI : out STD_LOGIC;
           CSN : out STD_LOGIC);
end toplevel;
--SCK : out STD_LOGIC;
           --MOSI : out STD_LOGIC;
           --CS : out STD_LOGIC
architecture Behavioral of toplevel is

component Reset_Delay IS	
    PORT (
        SIGNAL iCLK : IN std_logic;	
        SIGNAL oRESET : OUT std_logic
			);	
end component;
--component clk_enabler is
--	GENERIC (
--		CONSTANT cnt_max : integer := 124999999);      
--	port(	
--		clock:		in std_logic;	 
--		clk_en: 	out std_logic
--	);
--end component;
Component TTL_Serial_user_logic is
GENERIC(
CONSTANT cnt_max : integer := 13021);
    Port ( clk   : in STD_LOGIC;
           idata : in STD_LOGIC_VECTOR(15 downto 0);
           TX    : out STD_LOGIC);
end Component;

Component SPI_Controller is
Port ( iData  : in std_logic_vector(15 downto 0);
       CLK    : in std_logic;
       RST    : in std_logic;
       SDCLK  : out std_logic;
       MOSI   : out std_logic;
       CSN    : out std_logic);
end component;

Component Table is
    Port ( datain : in std_logic_vector(3 downto 0);
            hexn : out std_logic_vector(15 downto 0));
end Component;

Component db1 is
GENERIC (
CONSTANT CNTR_MAX : std_logic_vector(15 downto 0) := X"FFFF");  
Port ( BTN_I1     : in  STD_LOGIC;
       CLK1         : in  STD_LOGIC;
       BTN_O1     : out  STD_LOGIC;
       TOGGLE_O1 : out  STD_LOGIC);
end Component;

Component Counter is
Port ( clkc : in STD_LOGIC;
       EB : in STD_LOGIC;
       Cnten : in STD_LOGIC;
       Reset : in STD_LOGIC;
       data_O : out STD_LOGIC_VECTOR(3 downto 0));
end Component;



signal btno1   : std_logic;
signal toggle2 : std_logic;
signal toggle3 : std_logic;
signal reset_d : std_logic;
signal clk_en  : std_logic;
signal reset_m : std_logic;
signal count   : std_logic_vector(3 downto 0);
signal hexnum  : std_logic_vector(15 downto 0);

begin
reset_m <= reset_d or btno1;
Inst_rst : component Reset_Delay
port map(
    iclk => CLK, 
    oReset => reset_d   
);
--Inst_clk_en : component Clk_enabler
--port map(
--    clock => CLK, 
--    clk_en => clk_en   
--);
Inst_db1 : db1
    port map(
        BTN_I1 => reset,
        CLK1 => clk,
        BTN_O1 => btno1
    );
Inst_db2 : db1
    port map(
        BTN_I1 => cnten,
        CLK1 => clk,
        TOGGLE_O1 => toggle2
    );
Inst_db3 : db1
    port map(
        BTN_I1 => EB,
        CLK1 => clk,
        TOGGLE_O1 => toggle3
    );
Inst_c1 : Counter
    port map(
        clkc => clk,
        EB => toggle3,
        Cnten =>  toggle2,
        Reset => reset_m,
        data_O => count
    );

Inst_table1 : Table
    port map(
        datain => count,
        hexn => hexnum
    );
Inst_spi : SPI_Controller 
        port map (
            iData => hexnum,
            RST => reset_m,
            CLK => clk,
            SDCLK => sdclk,
            MOSI => MOSI,
            CSN => CSN
            );
   
Inst_ttl : TTL_Serial_user_logic
    port map(
        clk => clk,
        idata => hexnum,
        TX => TX
    );
    
end Behavioral;
