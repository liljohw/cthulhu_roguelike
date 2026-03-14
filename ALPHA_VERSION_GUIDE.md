# GUIA COMPLETO - VERSÃO ALPHA JOGÁVEL
## PtahsTale - Implementação Passo a Passo

---

## ?? SUMÁRIO

1. [Arquivos C++ Criados](#arquivos-cpp-criados)
2. [Configurações de Projeto](#configurações-de-projeto)
3. [Compilação do Código](#compilação-do-código)
4. [Configuração no Editor UE5](#configuração-no-editor-ue5)
5. [Sistema de Input](#sistema-de-input)
6. [Sistema de Combate](#sistema-de-combate)
7. [Sistema de Inimigos e IA](#sistema-de-inimigos-e-ia)
8. [Geração Procedural de Mapa](#geração-procedural-de-mapa)
9. [Menu Principal](#menu-principal)
10. [Sistema de Game Over](#sistema-de-game-over)
11. [Teste Final](#teste-final)

---

## 1. ARQUIVOS C++ CRIADOS ?

Os seguintes arquivos foram criados automaticamente:

### Sistema de Saúde
- `Source/PtahsTale/Combat/HealthComponent.h`
- `Source/PtahsTale/Combat/HealthComponent.cpp`

### Sistema de Projéteis
- `Source/PtahsTale/Combat/Projectile.h`
- `Source/PtahsTale/Combat/Projectile.cpp`

### Personagem Atualizado
- `Source/PtahsTale/PtahsTaleCharacter.h` (modificado com sprint e tiro)
- `Source/PtahsTale/PtahsTaleCharacter.cpp` (modificado)

---

## 2. CONFIGURAÇÕES DE PROJETO

### 2.1. Atualizar PtahsTale.Build.cs

**?? Arquivo:** `Source/PtahsTale/PtahsTale.Build.cs`

**Ação:** Substituir o conteúdo completo por:

```csharp
using UnrealBuildTool;

public class PtahStale : ModuleRules
{
	public PtahStale(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"PCG",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});
	}
}
```

---

## 3. COMPILAÇÃO DO CÓDIGO

### 3.1. Fechar o Editor Unreal Engine (se estiver aberto)

### 3.2. Compilar no Visual Studio

1. Abra a solução `PtahsTale.sln` no Visual Studio
2. No **Solution Explorer**, clique com botão direito em **PtahsTale** (projeto)
3. Selecione **Build**
4. Aguarde a compilação completar (**Build succeeded** deve aparecer)

### 3.3. Se houver erros de compilação:

#### Possível erro: "Não encontrou HealthComponent"
**Solução:** Verifique se o arquivo está na pasta correta: `Source/PtahsTale/Combat/`

#### Possível erro: "Projectile.h not found"
**Solução:** Regenere os arquivos do projeto:
1. Feche Visual Studio
2. Clique direito em `PtahsTale.uproject`
3. Selecione **Generate Visual Studio project files**
4. Abra novamente e compile

---

## 4. CONFIGURAÇÃO NO EDITOR UE5

### 4.1. Abrir o Projeto

1. Abra `PtahsTale.uproject` no Unreal Engine 5.4.4
2. Aguarde carregar (pode demorar alguns minutos na primeira vez)

---

## 5. SISTEMA DE INPUT

### 5.1. Criar Input Actions

**?? Localização:** Content Browser ? `Content/Input/Actions/`

1. Clique direito ? **Input** ? **Input Action**
2. Crie os seguintes Input Actions:

| Nome do Arquivo | Tipo de Valor |
|---|---|
| `IA_Move` | Input Action Value Type: **Axis2D (Vector 2D)** |
| `IA_Look` | Input Action Value Type: **Axis2D (Vector 2D)** |
| `IA_Jump` | Input Action Value Type: **Digital (bool)** |
| `IA_Shoot` | Input Action Value Type: **Digital (bool)** |
| `IA_Sprint` | Input Action Value Type: **Digital (bool)** |

### 5.2. Criar Input Mapping Context

**?? Localização:** Content Browser ? `Content/Input/`

1. Clique direito ? **Input** ? **Input Mapping Context**
2. Nomeie como `IMC_Default`
3. Abra e adicione os mappings:

| Input Action | Teclas/Mouse | Modificadores |
|---|---|---|
| `IA_Move` | W,A,S,D | W/S = Eixo Y, A/D = Eixo X |
| `IA_Look` | Mouse XY 2D-Axis | - |
| `IA_Jump` | Space | - |
| `IA_Shoot` | Left Mouse Button | - |
| `IA_Sprint` | Left Shift | - |

**Configuração detalhada:**

**IA_Move:**
- Adicione **Keyboard ? W**
  - Modifiers ? Swizzle Input Axis Values ? **Order: XZY**
- Adicione **Keyboard ? S**
  - Modifiers ? Swizzle Input Axis Values ? **Order: XZY**
  - Modifiers ? Negate ? **Y: true**
- Adicione **Keyboard ? A**
  - Modifiers ? Negate ? **X: true**
- Adicione **Keyboard ? D**
  - (sem modificadores)

**IA_Look:**
- Adicione **Mouse ? Mouse XY 2D-Axis**
  - (sem modificadores)

---

## 6. SISTEMA DE COMBATE

### 6.1. Criar Blueprint de Projétil

1. Content Browser ? `Content/Blueprints/Combat/`
2. Clique direito ? **Blueprint Class**
3. Parent Class: **Projectile** (procure por "Projectile" criado em C++)
4. Nome: `BP_Projectile`

**Configurar BP_Projectile:**

1. Abra `BP_Projectile`
2. **Components:**
   - Selecione **MeshComponent**
   - Em **Static Mesh**, escolha **Sphere** ou **Cube** (Engine Content)
   - Scale: `(0.2, 0.2, 0.2)`
3. **Detalhes (Class Defaults):**
   - **Damage:** `25.0`
   - **Life Span:** `3.0`
4. **ProjectileMovement Component:**
   - **Initial Speed:** `3000.0`
   - **Max Speed:** `3000.0`
5. **Compile** e **Save**

### 6.2. Criar Blueprint de Personagem do Jogador

1. Content Browser ? `Content/Blueprints/Player/`
2. Clique direito ? **Blueprint Class**
3. Parent Class: **PtahStaleCharacter** (seu C++ class)
4. Nome: `BP_PlayerCharacter`

**Configurar BP_PlayerCharacter:**

1. Abra `BP_PlayerCharacter`
2. **Class Defaults (painel direito):**
   - **Default Mapping Context:** Selecione `IMC_Default`
   - **Jump Action:** Selecione `IA_Jump`
   - **Move Action:** Selecione `IA_Move`
   - **Look Action:** Selecione `IA_Look`
   - **Shoot Action:** Selecione `IA_Shoot`
   - **Sprint Action:** Selecione `IA_Sprint`
   - **Projectile Class:** Selecione `BP_Projectile`
   - **Fire Rate:** `0.5`
   - **Walk Speed:** `500.0`
   - **Sprint Speed:** `800.0`
3. **Components:**
   - Selecione **HealthComponent**
   - **Max Health:** `100.0`
4. **Mesh Component:**
   - Adicione uma mesh temporária (ex: Engine Content ? Mannequin)
5. **Compile** e **Save**

---

## 7. SISTEMA DE INIMIGOS E IA

### 7.1. Criar Blueprint de Inimigo Base

**?? NOTA:** O arquivo BaseEnemy.h/.cpp já existe no projeto. Vamos criar o Blueprint.

1. Content Browser ? `Content/Blueprints/Enemies/`
2. Clique direito ? **Blueprint Class**
3. Parent Class: **BaseEnemy** (procure pelo C++ class)
4. Nome: `BP_BaseEnemy`

**Configurar BP_BaseEnemy:**

1. Abra `BP_BaseEnemy`
2. **Components:**
   - **Mesh:** Adicione uma mesh (cube colorido ou mannequin)
   - **Capsule Component:** Radius: `42`, Half Height: `96`
3. **Class Defaults:**
   - **Health Component ? Max Health:** `50.0`
   - **Attack Damage:** `10.0`
   - **Attack Range:** `200.0`
   - **Attack Cooldown:** `1.5`
   - **Detection Radius:** `1000.0`
   - **Chase Speed:** `400.0`
   - **Patrol Speed:** `200.0`
4. **Compile** e **Save**

### 7.2. Criar AI Controller

1. Content Browser ? `Content/Blueprints/AI/`
2. Clique direito ? **Blueprint Class**
3. Parent Class: **AIController**
4. Nome: `BP_EnemyAIController`

**Configurar BP_EnemyAIController:**

1. Abra `BP_EnemyAIController`
2. **Event Graph:**

```
Event BeginPlay
?
Move To Actor or Location
  - Target Actor: Get Player Character (cast to Actor)
  - Acceptance Radius: 100.0
```

3. **Compile** e **Save**

### 7.3. Configurar BP_BaseEnemy para usar AI

1. Abra `BP_BaseEnemy`
2. **Class Settings (toolbar)**
3. **Pawn ? AI Controller Class:** Selecione `BP_EnemyAIController`
4. **Compile** e **Save**

---

## 8. GERAÇÃO PROCEDURAL DE MAPA

### 8.1. Criar Blueprint de World Generator

1. Content Browser ? `Content/Blueprints/Procedural/`
2. Clique direito ? **Blueprint Class**
3. Parent Class: **ProceduralWorldGenerator** (C++ class)
4. Nome: `BP_WorldGenerator`

**Configurar BP_WorldGenerator:**

1. Abra `BP_WorldGenerator`
2. **Class Defaults:**
   - **Generation Params ? Room Count:** `15` (para 3 segmentos x 5 salas)
   - **Generation Params ? Primary Tag:** `Underground`
   - **Generation Params ? Mythos Clue Chance:** `0.2`
   - **Generation Params ? Encounter Chance:** `0.3`
   - **Generation Params ? Room Base Size:** `(1000, 1000, 400)`
3. **Event Graph:**

Adicione este Blueprint code:

```
Event BeginPlay
?
Generate (função do C++)
?
For Each Loop (Generated Rooms)
  ?
  Spawn Actor from Class
    - Class: Static Mesh Actor
    - Transform: Loop Body ? World Position
    - Static Mesh: Cube ou Floor
    - Scale: Room ? Half Extents / 100
  ?
  (Condicional) If Has Encounter
    ?
    Spawn Actor from Class
      - Class: BP_BaseEnemy
      - Transform: Room ? World Position + (0, 0, 100)
```

4. **Compile** e **Save**

### 8.2. Criar Mapa de Teste

1. **File ? New Level ? Empty Level**
2. Salve como `TestDungeon` em `Content/Maps/`
3. Arraste `BP_WorldGenerator` para o level
4. **World Settings ? GameMode Override:** (veja próximo passo)

---

## 9. MENU PRINCIPAL

### 9.1. Criar Widget do Menu Principal

1. Content Browser ? `Content/UI/`
2. Clique direito ? **User Interface ? Widget Blueprint**
3. Nome: `WBP_MainMenu`

**Design do WBP_MainMenu:**

1. Abra `WBP_MainMenu`
2. **Designer Tab:**
   - Adicione **Canvas Panel** (root)
   - Adicione **Vertical Box** (centralize na tela)
   - Dentro do Vertical Box, adicione:
     - **Text Block:** "PTAH'S TALE" (Title)
     - **Button:** "Start Game"
     - **Button:** "Quit"

3. **Graph Tab:**

**Botão Start Game:**
```
On Clicked (Event)
?
Open Level (by Name)
  - Level Name: "TestDungeon"
```

**Botão Quit:**
```
On Clicked (Event)
?
Quit Game
```

4. **Compile** e **Save**

### 9.2. Criar Mapa de Menu

1. **File ? New Level ? Default**
2. Salve como `MainMenu` em `Content/Maps/`
3. Delete todos os atores (Player Start, Light, etc)
4. **Level Blueprint:**

```
Event BeginPlay
?
Create Widget
  - Class: WBP_MainMenu
?
Add to Viewport
?
Set Show Mouse Cursor (true)
?
Set Input Mode UI Only
```

5. **Save**

### 9.3. Configurar como Default Map

1. **Edit ? Project Settings**
2. **Maps & Modes**
3. **Default Maps:**
   - **Editor Startup Map:** `MainMenu`
   - **Game Default Map:** `MainMenu`
4. **Close**

---

## 10. SISTEMA DE GAME OVER

### 10.1. Criar Widget de Game Over

1. Content Browser ? `Content/UI/`
2. Clique direito ? **User Interface ? Widget Blueprint**
3. Nome: `WBP_GameOver`

**Design do WBP_GameOver:**

1. **Designer:**
   - **Canvas Panel**
   - **Vertical Box** (centralized)
     - **Text:** "GAME OVER"
     - **Button:** "Restart"
     - **Button:** "Main Menu"

2. **Graph:**

**Botão Restart:**
```
On Clicked
?
Open Level (by Name)
  - Level Name: "TestDungeon"
```

**Botão Main Menu:**
```
On Clicked
?
Open Level (by Name)
  - Level Name: "MainMenu"
```

3. **Compile** e **Save**

### 10.2. Configurar Game Over no Player

1. Abra `BP_PlayerCharacter`
2. **Event Graph:**

```
Event BeginPlay
?
(Get HealthComponent)
?
Bind Event to On Death
  ?
  Create Widget (WBP_GameOver)
  ?
  Add to Viewport
  ?
  Set Show Mouse Cursor (true)
  ?
  Set Input Mode UI Only
  ?
  Set Game Paused (true)
```

3. **Compile** e **Save**

---

## 11. TESTE FINAL

### 11.1. Checklist antes de testar:

- [ ] Código C++ compilou sem erros
- [ ] Input Actions criados (IA_Move, IA_Look, IA_Jump, IA_Shoot, IA_Sprint)
- [ ] Input Mapping Context configurado (IMC_Default)
- [ ] BP_Projectile criado e configurado
- [ ] BP_PlayerCharacter criado e configurado com inputs
- [ ] BP_BaseEnemy criado
- [ ] BP_EnemyAIController criado
- [ ] BP_WorldGenerator criado
- [ ] TestDungeon map criado com World Generator
- [ ] WBP_MainMenu criado
- [ ] MainMenu map criado
- [ ] WBP_GameOver criado
- [ ] Project Settings ? Default Maps configurados

### 11.2. Como Testar:

1. **Play from Main Menu:**
   - Clique **Play** no editor
   - Deve abrir o menu principal
   - Clique "Start Game"

2. **Testar Movimento:**
   - **W,A,S,D** para mover
   - **Space** para pular
   - **Shift** para correr
   - **Mouse** para olhar ao redor

3. **Testar Tiro:**
   - **Left Mouse Button** para atirar
   - Projéteis devem spawnar e voar

4. **Testar Inimigos:**
   - Inimigos devem aparecer no mapa procedural
   - Devem perseguir o jogador quando próximos
   - Atirar nos inimigos deve causar dano

5. **Testar Game Over:**
   - Deixe os inimigos atacarem até sua vida zerar
   - Widget de Game Over deve aparecer

---

## 12. TROUBLESHOOTING

### Problema: Personagem não se move
**Solução:** Verifique se IMC_Default está atribuído em BP_PlayerCharacter

### Problema: Tiro não funciona
**Solução:** Verifique se BP_Projectile está atribuído em Projectile Class

### Problema: Inimigos não aparecem
**Solução:** Certifique-se que BP_WorldGenerator chamou Generate() no BeginPlay

### Problema: Game Over não aparece
**Solução:** Verifique se o evento On Death está bound no Event Graph

---

## 13. MELHORIAS FUTURAS (PÓS-ALPHA)

- [ ] Adicionar animações para personagem e inimigos
- [ ] Adicionar sons de tiro, dano, morte
- [ ] Adicionar HUD com vida do jogador
- [ ] Melhorar geração de mapa com corredores
- [ ] Adicionar diferentes tipos de inimigos
- [ ] Adicionar sistema de armas diferentes
- [ ] Adicionar pickups (munição, vida)

---

## ? CONCLUSÃO

Após seguir este guia, você terá uma versão alpha jogável com:
- ? Movimento (andar, pular, correr)
- ? Sistema de tiro
- ? Menu principal
- ? Mapa procedural com salas
- ? Inimigos com IA
- ? Sistema de dano
- ? Game Over

**Divirta-se testando! ??**
