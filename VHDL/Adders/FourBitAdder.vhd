----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/04/2018 10:47:56 AM
-- Design Name: 
-- Module Name: FullAdder - Behavioral
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
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity FourBitAdder is
    Port ( A : in STD_LOGIC_Vector (3 downto 0);
           B : in STD_LOGIC_Vector (3 downto 0);
           Cin : in STD_LOGIC;
           Sum : inout STD_LOGIC_Vector (3 downto 0);
           Cout : inout STD_LOGIC;
           OVER : inout std_logic);
          
end FourBitAdder;

architecture Behavioral of FourBitAdder is

component FullAdder
   port(
        A : in std_logic;
        B : in std_logic;
        Cin : in std_logic;
        Sum : out std_logic;
        Cout : out std_logic
       );
   end component;

signal Cout2, Cout3, Cout4, Cin2, Cin3, Cin4 : std_logic:='0';

begin

    FA1 : FullAdder port map (
         A => A(0),
         B => B(0),
         Cin=>'0',
         Sum => Sum(0),
         Cout => Cout
       ); 
    FA2 : FullAdder port map (
         A => A(1),
         B => B(1),
         Cin=>Cout,
         Sum => Sum(1),
         Cout => Cout2
       );
    FA3 : FullAdder port map (
         A => A(2),
         B => B(2),
         Cin=>Cout2,
         Sum => Sum(2),
         Cout => Cout3
       );      
     FA4 : FullAdder port map (
          A => A(3),
          B => B(3),
          Cin=>Cout3,
          Sum => Sum(3),
          Cout => Cout4
      );  
      
      OVER <= (A(3) xor B(3)) xor (Cout4 xor Sum(3));

end;
