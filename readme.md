
# 🧱 Sistema de Bordas com GangZone (SA:MP)

**Autor:** Galo HigorNRX  
**Data:** 22/06/2025  
**Versão:** v0.0.0

---

## 📌 Descrição

Sistema para criar **bordas visuais dinâmicas** em torno de uma área específica no mapa utilizando múltiplas `GangZones` no SA:MP.  
Ideal para delimitar zonas de evento, áreas seguras, regiões de combate e muito mais com alta precisão e visibilidade para o jogador.

---

## ⚙️ Funções

### ✅ Criar Borda de GangZone

```pawn
BorderGangZoneCreate(Float:TMaxX, Float:TMaxY, Float:TMinX, Float:TMinY, Float:BMaxX, Float:BMaxY, Float:BMinX, Float:BMinY)
```

| Parâmetro     | Descrição                                                                 |
|---------------|---------------------------------------------------------------------------|
| `TMaxX/Y`     | Coordenadas máximas da área total                                          |
| `TMinX/Y`     | Coordenadas mínimas da área total                                          |
| `BMaxX/Y`     | Coordenadas máximas da zona interna ("zona útil")                         |
| `BMinX/Y`     | Coordenadas mínimas da zona interna ("zona útil")                         |

- Cria automaticamente uma borda com 4 zonas ao redor da região central.
- Use `0` para tamanho total do mapa se necessário.
- Retorno:
  - `-1` → Falha na criação
  - `ID` → Sucesso, retorna ID da borda criada

---

### ❌ Destruir Borda

```pawn
BorderGangZoneDestroy(ID_BorderZone)
```

Remove completamente a borda da gangzone vinculada ao ID.

---

### 🛡️ Verificar Validade

```pawn
IsValidBorderGangZone(ID_BorderZone)
```

Verifica se o ID fornecido corresponde a uma borda válida.

---

### 👁️ Mostrar para Jogador

```pawn
BorderGangZoneShowForPlayer(playerid, ID_BorderZone, color)
```

Exibe a borda da gangzone para o jogador com a cor definida.

---

### 🙈 Esconder de Jogador

```pawn
BorderGangZoneHideForPlayer(playerid, ID_BorderZone)
```

Oculta a visualização da borda da gangzone para o jogador.

---

### ⚡ Flash Visual

```pawn
BorderGangZoneFlashForPlayer(playerid, ID_BorderZone, color)
```

Faz a borda piscar (flash) para o jogador com a cor especificada.

---

## 🧭 Esquema Visual

```
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
TMaxX > *-------------------------------------  
        ^
      TMaxY
```

---

## 🧪 Exemplo de Uso

```pawn
new borderID = BorderGangZoneCreate(
    3000.0, 3000.0,     // TMaxX, TMaxY
    1000.0, 1000.0,     // TMinX, TMinY
    2600.0, 2600.0,     // BMaxX, BMaxY
    1400.0, 1400.0      // BMinX, BMinY
);

if (borderID != -1)
{
    BorderGangZoneShowForPlayer(playerid, borderID, 0xFF0000AA);
}
```

---

## 📄 Licença

Este sistema é fornecido **"como está"**.  
Você pode modificá-lo livremente, **mantendo os créditos ao autor original**.

---

**Desenvolvido por Galo HigorNRX com 💡 e criatividade**
