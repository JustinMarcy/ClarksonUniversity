-- Code your design here
library ieee;
use ieee.std_logic_1164.all;

entity myForwardingUnit is
   port( 
    Rn, Rm  : in std_logic_vector(4 downto 0);
    EXMEMRD  : in std_logic_vector(4 downto 0);
 	EXMEMregwrite : in std_logic;	
 	MEMWBRD  : in std_logic_vector(4 downto 0);
    MEMWBregwrite : in std_logic;	
    ForwardA  : out std_logic_vector(1 downto 0);
	ForwardB  : out std_logic_vector(1 downto 0));
end myForwardingUnit;
 
architecture behavior of myForwardingUnit is

--signal EX/MEM.RegWrite : std_logic_vector(96 downto 0);
--signal EX/MEM.RegisterRd :
--signal ID/EX.RegisterRn :
--signal ID/EX.RegisterRm :
--signal MEM/WB.RegWrite : 
--signal MEM/WB.RegisterRd : 

begin
  
--  mytest_01: process (Rn, EXMEMrd)
--	begin  
--	if (Rn = EXMEMrd) then
--      ForwardA <= "01" ;
--    else
--      ForwardA <= "00" ;
--	end if;
--    end process;
    
   
    
    F_Unit: process (Rn, EXMEMrd) 
    begin
    -----------------EX Hazard----------------------
    if (EX/MEM.RegWrite and (EX/MEM.RegisterRd ? 31)
    and (EX/MEM.RegisterRd = ID/EX.RegisterRn)) then 
    ForwardA = "10"
  
    if (EX/MEM.RegWrite and (EX/MEM.RegisterRd ? 31)
    and (EX/MEM.RegisterRd = ID/EX.RegisterRm)) ForwardB = "10"
    ------------------------------------------------
    
--    -----------------MEM Hazard---------------------
--    if (MEM/WB.RegWrite
--    and (MEM/WB.RegisterRd ? 31)
--    and not(EX/MEM.RegWrite and (EX/MEM.RegisterRd ? 31)
--    and (EX/MEM.RegisterRd = ID/EX.RegisterRn))
--    and (MEM/WB.RegisterRd = ID/EX.RegisterRn)) ForwardA = 01
    
--    if (MEM/WB.RegWrite
--    and (MEM/WB.RegisterRd ? 31)
--    and not(EX/MEM.RegWrite and (EX/MEM.RegisterRd ? 31)
--    and (EX/MEM.RegisterRd = ID/EX.RegisterRm))
--    and (MEM/WB.RegisterRd = ID/EX.RegisterRm)) ForwardB = 01
--    -------------------------------------------------
    end process;
    
end behavior;