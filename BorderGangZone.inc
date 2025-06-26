// Bordas funcionais usando GangZone o mapa...etc
// by Galo HigorNRX 22/06/2025
// v0.0.0

/*                  D O C U M E N T A Ç Â O

Fuctions
    // BorderGangZoneCreate(Float:TMaxX, Float:TMaxY, Float:TMinX, Float:TMinY, Float:BMaxX, Float:BMaxY, Float:BMinX, Float:BMinY)
        Criar bordar de gangzone em uma determinada area
        Posição com 0 criar no tamanho total do mapa, retorna ID ou -1 se a criação falhar

                                                            TMinY
                                                             v
                        -------------------------------------* < TMinX
                        |                    BMinY           |
                        |    In Zone           v             |
                        |         -------------* < BMinX     |
                        |         |            |             |
                        |         | Out Zone   |             |
                        |         |            |             |
                        |         |            |             |
                        | BMaxX > *-------------             |
                        |         ^                          |  
                        |        BMaxY                       |
              TMaxX  >  *-------------------------------------  
                        ^
                      TMaxY

        
    // BorderGangZoneDestroy(ID_BorderZone)
        Destruir bordar de gangzone
    // IsValidBorderGangZone(ID_BorderZone)  
        Verificar se e um ID validor  
    // BorderGangZoneShowForPlayer(playerid, ID_BorderZone, color)
        Mostrar um BorderGangZone para o jogador
    // BorderGangZoneHideForPlayer(playerid, ID_BorderZone)
        Ocultar um bordergangzone para o jogador
    // BorderGangZoneFlashForPlayer(playerid, ID_BorderZone, color)
        Flash em um BorderGangZone para o Jogador
*/


// CFG's
    #define MAX_BORDER_GANGZONES            12                          // Total de BorderGangZone possiveis
    #define MAX_IDS_BORDER_GANGZONES        256                         // Total de BorderGangZone que o sistema pode criar

// Database
  enum DataBorderGangZone
    {	
        bool:Used_BorderGangZone, // Controlar ID vazios

        // tamanho total da zona
        Float:TMaxX_BorderGangZone, 
        Float:TMaxY_BorderGangZone, 
        Float:TMinX_BorderGangZone,
        Float:TMinY_BorderGangZone, 

        // tamanho total dentro da zona
        Float:BMaxX_BorderGangZone, 
        Float:BMaxY_BorderGangZone, 
        Float:BMinX_BorderGangZone,
        Float:BMinY_BorderGangZone, 

        // ID's da GangZones
        BGGangZone1,
        BGGangZone2,
        BGGangZone3,
        BGGangZone4,
    };

    new IDBorderGangZone[MAX_BORDER_GANGZONES][DataBorderGangZone];
// Body
    // Criar bordar de gangzone
    BorderGangZoneCreate(Float:TMaxX, Float:TMaxY, Float:TMinX, Float:TMinY, Float:BMaxX, Float:BMaxY, Float:BMinX, Float:BMinY)
    {  
        new ID_BorderGangZone;

        // Atribuir um ID começando por ID
        for(new x = 0; x < MAX_BORDER_GANGZONES; x++)      
        {
            if(!IDBorderGangZone[x][Used_BorderGangZone]) // Verificar se o Slot da area, está vazio
            {
                IDBorderGangZone[x][Used_BorderGangZone]    = true;
                ID_BorderGangZone                           = x;
                break;
            }
            else if(x == MAX_BORDER_GANGZONES - 1)
                return -1;
        }

        //FixAreaPositionOrder();

        // Definir para todo o mapa
        if(TMaxX == 0 && TMaxY == 0 && TMinX == 0 && TMinY == 0) 
        {
            TMaxX = -2989.536;
            TMaxY = -3328.195;
            TMinX = 2989.536;
            TMinY = 2989.536;
        }
        // tamanho total da zona
        IDBorderGangZone[ID_BorderGangZone][TMaxX_BorderGangZone]   = TMaxX;
        IDBorderGangZone[ID_BorderGangZone][TMaxY_BorderGangZone]   = TMaxY;
        IDBorderGangZone[ID_BorderGangZone][TMinX_BorderGangZone]   = TMinX;
        IDBorderGangZone[ID_BorderGangZone][TMinY_BorderGangZone]   = TMinY;
        IDBorderGangZone[ID_BorderGangZone][BMaxX_BorderGangZone]   = BMaxX;
        IDBorderGangZone[ID_BorderGangZone][BMaxY_BorderGangZone]   = BMaxY;
        IDBorderGangZone[ID_BorderGangZone][BMinX_BorderGangZone]   = BMinX;
        IDBorderGangZone[ID_BorderGangZone][BMinY_BorderGangZone]   = BMinY;

        // Borda Superior: horizontal no topo
        IDBorderGangZone[ID_BorderGangZone][BGGangZone1] = GangZoneCreate(
            BMinX, TMinY,  // começa na borda interna esquerda
            BMaxX, BMinY   // termina na borda interna superior
        );

        // Borda Inferior: horizontal na base
        IDBorderGangZone[ID_BorderGangZone][BGGangZone2] = GangZoneCreate(
            BMinX, BMaxY,  // começa na borda interna esquerda
            BMaxX, TMaxY   // termina na borda externa inferior
        );

        // Borda Esquerda: vertical na esquerda
        IDBorderGangZone[ID_BorderGangZone][BGGangZone3] = GangZoneCreate(
            TMinX, TMinY,  // topo externo
            BMinX, TMaxY   // base externa
        );

        // Borda Direita: vertical na direita
        IDBorderGangZone[ID_BorderGangZone][BGGangZone4] = GangZoneCreate(
            BMaxX, TMinY,  // topo externo
            TMaxX, TMaxY   // base externa
        );
        return ID_BorderGangZone;
    }
    // Destruir bordar de gangzone
    BorderGangZoneDestroy(ID_BorderZone)
    {
        if (!IsValidBorderGangZone(ID_BorderZone))
            return 0;

        GangZoneHideForAll(IDBorderGangZone[ID_BorderZone][BGGangZone1]);
        GangZoneHideForAll(IDBorderGangZone[ID_BorderZone][BGGangZone2]);
        GangZoneHideForAll(IDBorderGangZone[ID_BorderZone][BGGangZone3]);
        GangZoneHideForAll(IDBorderGangZone[ID_BorderZone][BGGangZone4]);

        new IDBorderGangZoneRaw[DataBorderGangZone];
        IDBorderGangZone[ID_BorderZone] = IDBorderGangZoneRaw; 
        return 1;
    }
    // verificar se um ID e validor
    IsValidBorderGangZone(ID_BorderZone)
    {
        if (ID_BorderZone < 0 || ID_BorderZone >= MAX_BORDER_GANGZONES)
            return 0;

        if(!IDBorderGangZone[ID_BorderZone][Used_BorderGangZone])
            return 0;

        return 1;
    }

// Players
    // Mostrar um BorderGangZone para o jogador
    BorderGangZoneShowForPlayer(playerid, ID_BorderZone, color)
    {
        if (!IsValidBorderGangZone(ID_BorderZone))
            return 0;

        if(!IsPlayerConnected(playerid))
            return 0;

        GangZoneShowForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone1], color);
        GangZoneShowForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone2], color);
        GangZoneShowForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone3], color);
        GangZoneShowForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone4], color);
        return 1;
    }
    // Ocultar um bordergangzone para o jogador
    BorderGangZoneHideForPlayer(playerid, ID_BorderZone)
    {
        if (!IsValidBorderGangZone(ID_BorderZone))
            return 0;

        if(!IsPlayerConnected(playerid))
            return 0;

        GangZoneHideForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone1]);
        GangZoneHideForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone2]);
        GangZoneHideForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone3]);
        GangZoneHideForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone4]);
        return 1;
    }
    // Flash em um BorderGangZone para o Jogador
    BorderGangZoneFlashForPlayer(playerid, ID_BorderZone, color)
    {
        if (!IsValidBorderGangZone(ID_BorderZone))
            return 0;

        if(!IsPlayerConnected(playerid))
            return 0;

        GangZoneFlashForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone1], color);
        GangZoneFlashForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone2], color);
        GangZoneFlashForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone3], color);
        GangZoneFlashForPlayer(playerid, IDBorderGangZone[ID_BorderZone][BGGangZone4], color);
        return 1;
    }


