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

### 5.1. Input Actions - Assets Existentes e Novos

**?? Localização:** Content Browser ? `Content/ThirdPerson/Input/Actions/`

**? JÁ EXISTENTES NO PROJETO:**
- `IA_Move` - Input Action Value Type: **Axis2D (Vector 2D)**
- `IA_Look` - Input Action Value Type: **Axis2D (Vector 2D)**
- `IA_Jump` - Input Action Value Type: **Digital (bool)**

**?? A CRIAR:**
1. No Content Browser, navegue para `Content/ThirdPerson/Input/Actions/`
2. Clique direito ? **Input** ? **Input Action**
3. Crie os seguintes Input Actions:

| Nome do Arquivo | Tipo de Valor |
|---|---|
| `IA_Shoot` | Input Action Value Type: **Digital (bool)** |
| `IA_Sprint` | Input Action Value Type: **Digital (bool)** |

### 5.2. Input Mapping Context - Usar Existente

**?? Localização:** Content Browser ? `Content/ThirdPerson/Input/`

**? JÁ EXISTE:** `IMC_Default.uasset`

**Ação:** Atualizar o mapping context existente:

1. Abra `IMC_Default` (duplo clique)
2. Verifique se os mappings existentes estão configurados:

| Input Action | Teclas/Mouse | Modificadores |
|---|---|---|
| `IA_Move` | W,A,S,D | W/S = Eixo Y, A/D = Eixo X |
| `IA_Look` | Mouse XY 2D-Axis | - |
| `IA_Jump` | Space | - |

3. **Adicione os novos mappings:**

| Input Action | Teclas/Mouse | Modificadores |
|---|---|---|
| `IA_Shoot` | Left Mouse Button | - |
| `IA_Sprint` | Left Shift | - |

4. **Save**

**Configuração detalhada de IA_Move (se necessário ajustar):**
- **Keyboard ? W**
  - Modifiers ? Swizzle Input Axis Values ? **Order: XZY**
- **Keyboard ? S**
  - Modifiers ? Swizzle Input Axis Values ? **Order: XZY**
  - Modifiers ? Negate ? **Y: true**
- **Keyboard ? A**
  - Modifiers ? Negate ? **X: true**
- **Keyboard ? D**
  - (sem modificadores)

**IA_Look:**
- **Mouse ? Mouse XY 2D-Axis**
  - (sem modificadores)

---

## 6. SISTEMA DE COMBATE

### 6.1. Criar Blueprint de Projétil

1. Content Browser ? Crie a pasta `Content/Blueprints/Combat/` (clique direito ? New Folder)
2. Dentro de `Combat/`, clique direito ? **Blueprint Class**
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

**? NOTA:** O projeto já possui `Content/ThirdPerson/Blueprints/BP_ThirdPersonCharacter` que pode ser usado para testes iniciais.

**Para criar um novo baseado no seu C++ Character:**

1. Content Browser ? Crie a pasta `Content/Blueprints/Player/` (se não existir)
2. Clique direito ? **Blueprint Class**
3. Parent Class: **PtahStaleCharacter** (procure pelo seu C++ class)
4. Nome: `BP_PlayerCharacter`

**Configurar BP_PlayerCharacter:**

1. Abra `BP_PlayerCharacter`
2. **Class Defaults (painel direito):**
   - **Default Mapping Context:** Selecione `IMC_Default` (de ThirdPerson/Input/)
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

1. Content Browser ? Crie a pasta `Content/Blueprints/Enemies/` (se não existir)
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

1. Content Browser ? Crie a pasta `Content/Blueprints/AI/` (se não existir)
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

1. Content Browser ? Crie a pasta `Content/Blueprints/Procedural/` (se não existir)
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

### 8.2. Criar ou Usar Mapa de Teste

**? OPÇÃO 1: Usar Mapa Existente para Testes Rápidos**
- O projeto já possui `Content/ThirdPerson/Maps/ThirdPersonMap.umap`
- Abra este mapa para testes iniciais

**?? OPÇÃO 2: Criar Novo Mapa para Sistema Procedural**

1. **File ? New Level ? Empty Level**
2. Crie a pasta `Content/Maps/` (se não existir)
3. Salve como `TestDungeon` em `Content/Maps/`
4. Arraste `BP_WorldGenerator` para o level
5. **World Settings ? GameMode Override:** (configure nas próximas seções)

---

## 9. MENU PRINCIPAL

### 9.1. Criar Widget do Menu Principal

1. Content Browser ? Crie a pasta `Content/UI/` (se não existir)
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
  - Level Name: "TestDungeon" ou "ThirdPersonMap"
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

1. Content Browser ? Use a pasta `Content/UI/` (criada anteriormente)
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
On Clicked (Event)
?
Get Current Level Name
?
Open Level (by Name)
  - Level Name: (use o nome retornado)
```

**Botão Main Menu:**
```
On Clicked (Event)
?
Open Level (by Name)
  - Level Name: "MainMenu"
```

3. **Compile** e **Save**

### 10.2. Conectar ao Sistema de Saúde

No **HealthComponent.cpp** (se ainda não implementado), adicione:

```cpp
// Quando a vida chegar a zero
if (Health <= 0.0f)
{
    OnDeath.Broadcast();
}
```

No **BP_PlayerCharacter**, Event Graph:

```
Event On Death (do HealthComponent)
?
Create Widget
  - Class: WBP_GameOver
?
Add to Viewport
?
Set Show Mouse Cursor (true)
?
Set Input Mode UI Only
?
Set Game Paused (true)
```

---

## 11. TESTE FINAL

### 11.1. Teste Rápido com Assets Existentes

1. Abra `Content/ThirdPerson/Maps/ThirdPersonMap`
2. Pressione **Play** (Alt+P)
3. Teste movimento (WASD), câmera (Mouse), pulo (Space)

### 11.2. Teste Completo do Sistema

1. Certifique-se de que todos os Blueprints estão salvos e compilados
2. Feche o editor e reabra o projeto
3. O `MainMenu` deve abrir automaticamente
4. Clique em "Start Game"
5. Teste:
   - Movimento e câmera
   - Sprint (Shift)
   - Pulo (Space)
   - Tiro (Left Mouse Button)
   - Colisão com inimigos
   - Sistema de dano
   - Game Over ao morrer

### 11.3. Debugging

Se algo não funcionar:

1. **Verifique o Output Log** (Window ? Developer Tools ? Output Log)
2. **Verifique as referências** nos Blueprints (procure por "?" ou broken references)
3. **Recompile** todos os Blueprints
4. **Regenere** os project files do Visual Studio

---

## ? CHECKLIST FINAL

- [ ] Todos os arquivos C++ compilam sem erros
- [ ] Input Actions criados (IA_Shoot, IA_Sprint)
- [ ] IMC_Default atualizado com novos mappings
- [ ] BP_Projectile criado e configurado
- [ ] BP_PlayerCharacter criado e configurado
- [ ] BP_BaseEnemy criado e configurado
- [ ] BP_EnemyAIController criado
- [ ] BP_WorldGenerator criado (opcional para alpha)
- [ ] WBP_MainMenu criado
- [ ] WBP_GameOver criado
- [ ] Maps configurados (MainMenu, TestDungeon ou ThirdPersonMap)
- [ ] Teste de gameplay funcionando

---

## ?? RECURSOS DISPONÍVEIS NO PROJETO

### Assets Já Presentes:
- `Content/ThirdPerson/` - Template completo de third person
- `Content/Assets/LevelPrototyping/` - Geometria básica para testes
- `Content/Assets/Weapons_Free/` - Modelos de armas
- `Content/Assets/Military_Free/` - Assets militares
- `Content/StarterContent/` - Content padrão do UE5

### Use estes assets para:
- Meshes de teste para projéteis
- Meshes para inimigos
- Decoração de níveis
- Props diversos

---

**Última Atualização:** 2024
**Versão do UE:** 5.4.4
**Projeto:** PtahsTale (Cthulhu Roguelike)
