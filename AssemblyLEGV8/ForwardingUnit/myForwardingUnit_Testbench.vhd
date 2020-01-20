--Code your testbench here
-- or browse Examples
-- Code your testbench here
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
entity myForwardingUnit_Testbench is
end myForwardingUnit_Testbench;

architecture Behavior of myForwardingUnit_Testbench is
 -- Component declaration

	component myForwardingUnit is
   port( 
     Rn, Rm  : in std_logic_vector(4 downto 0);
     EXMEMRD  : in std_logic_vector(4 downto 0);
 	 EXMEMregwrite : in std_logic;	
 	MEMWBRD  : in std_logic_vector(4 downto 0);
    MEMWBregwrite : in std_logic;	
    ForwardA  : out std_logic_vector(1 downto 0);
	ForwardB  : out std_logic_vector(1 downto 0));
end component;

    signal Rn_tb, Rm_tb, MEMWBRD_tb, EXMEMRD_tb : std_logic_vector(4 downto 0);
    signal ForwardA_tb, ForwardB_tb : std_logic_vector (1 downto 0);
    signal EXMEMregwrite_tb, MEMWBregwrite_tb: std_logic;

begin
  
  myForwardingUnit_test : myForwardingUnit port map (Rn_tb, Rn_tb, EXMEMRD_tb, EXMEMregwrite_tb, MEMWBRD_tb, MEMWBregwrite_tb, ForwardA_tb, ForwardB_tb );

  process begin
     Rn_tb <= "00001";
     EXMEMrd_tb <= "00001";
     wait for 10 ns;
     Rn_tb <= "00101";
     EXMEMrd_tb <= "00001";
	wait for 10 ns;
    wait;
  end process; 
  
end Behavior;