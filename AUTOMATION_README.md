# ?? AUTOMAÇÃO DO SETUP ALPHA - PTAHSTALE

Este documento explica como usar os scripts de automação para configurar o projeto PtahsTale para a versão Alpha jogável.

---

## ?? O QUE FOI AUTOMATIZADO

### ? Totalmente Automatizado (Script PowerShell)
- ? Validação de estrutura do projeto
- ? Validação de arquivos C++ necessários
- ? Criação de pastas de organização (Blueprints, UI, Maps)
- ? Atualização do arquivo `.Build.cs` com módulos necessários
- ? Compilação do projeto (via MSBuild)
- ? Geração de relatório de setup

### ?? Semi-Automatizado (Script Python no UE5 Editor)
- ?? Criação de Input Actions (IA_Shoot, IA_Sprint)
- ?? Criação de Blueprints base (BP_Projectile, BP_PlayerCharacter, etc)
- ?? Criação de Widgets (WBP_MainMenu, WBP_GameOver)

### ? Precisa Ser Manual
- ? Configuração detalhada de Blueprints
- ? Layout de UI
- ? Mappings de Input Context
- ? Level design

---

## ?? COMO USAR

### Etapa 1: Script PowerShell (Fora do Editor)

**O que faz:** Valida estrutura, cria pastas, atualiza Build.cs, compila

**Como executar:**

```powershell
# Navegue até a pasta do projeto
cd "D:\Games\UE 5.4.4\Ptahs Tale\PtahsTale"

# Execute o script
.\Tools\AlphaSetup.ps1
```

**Opções disponíveis:**

```powershell
# Apenas validar, sem fazer mudanças
.\Tools\AlphaSetup.ps1 -ValidateOnly

# Pular compilação
.\Tools\AlphaSetup.ps1 -SkipBuild

# Modo verbose (mais detalhes)
.\Tools\AlphaSetup.ps1 -Verbose
```

**Output esperado:**
```
==> Validando estrutura do projeto...
    ? Pasta de código fonte encontrado
    ? Pasta de conteúdo encontrado
    ? Arquivo de projeto UE encontrado

==> Validando arquivos C++ necessários...
    ? Combat\HealthComponent.h
    ? Combat\Projectile.h
    ...

==> Criando pastas necessárias...
    ? Criada: Blueprints\Combat
    ? Criada: Blueprints\Player
    ...

==> Atualizando configuração de build...
    ? Build.cs atualizado com sucesso

==> Compilando projeto...
    Compilando (isso pode demorar alguns minutos)...
    ? Compilação concluída com sucesso!

==> Gerando relatório de setup...
    ? Relatório salvo em: SETUP_REPORT.md

?????????????????????????????????????????????????????????
?  ? SETUP AUTOMÁTICO CONCLUÍDO                       ?
?????????????????????????????????????????????????????????
```

**Após executar:**
- Leia o arquivo `SETUP_REPORT.md` gerado
- Continue para a Etapa 2

---

### Etapa 2: Script Python (Dentro do Editor UE5)

**O que faz:** Cria Input Actions e Blueprints base

**Como executar:**

#### Método 1: Via Output Log (Recomendado)

1. Abra o projeto `PtahsTale.uproject` no UE5 Editor
2. Aguarde carregar completamente
3. Menu: **Window ? Developer Tools ? Output Log**
4. Na janela Output Log, clique na aba **"Python"**
5. Cole e execute:

```python
exec(open('Content/Python/AlphaSetup.py').read())
```

6. Aguarde conclusão (verificar logs)

#### Método 2: Via Python Console

1. Menu: **Window ? Developer Tools ? Python Console**
2. Cole e execute:

```python
exec(open('Content/Python/AlphaSetup.py').read())
```

#### Método 3: Via Editor Utility Widget (Mais Avançado)

1. Crie um **Editor Utility Widget** chamado `EUW_AlphaSetup`
2. Adicione um botão "Run Setup"
3. No Event Graph do botão, adicione:
   - **Execute Console Command**: `py Content/Python/AlphaSetup.py`
4. Salve e execute via **Tools ? Editor Utility Widgets ? EUW_AlphaSetup**

**Output esperado:**

```
============================================================
PTAHSTALE - ALPHA VERSION SETUP (Python)
Criando Input Actions e Blueprints base...
============================================================

==> Validando assets existentes...
    ? IA_Move encontrado
    ? IA_Look encontrado
    ? IA_Jump encontrado
    ? IMC_Default encontrado

==> Criando Input Actions...
    ? Criado: IA_Shoot - Ação de atirar
    ? Criado: IA_Sprint - Ação de correr

==> Criando BP_Projectile...
    ? BP_Projectile criado com sucesso
    ? Configure manualmente: Mesh, Damage, ProjectileMovement

==> Criando BP_PlayerCharacter...
    ? BP_PlayerCharacter criado com sucesso
    ? Configure manualmente: Input Actions, Projectile Class, etc

==> Criando BP_BaseEnemy...
    ? BP_BaseEnemy criado com sucesso
    ? Configure manualmente: Mesh, Stats, AI Controller

==> Criando BP_EnemyAIController...
    ? BP_EnemyAIController criado com sucesso
    ? Configure manualmente: Behavior Tree, Event Graph

==> Criando WBP_MainMenu...
    ? WBP_MainMenu criado com sucesso
    ? Configure manualmente: UI Layout, Botões, Events

==> Criando WBP_GameOver...
    ? WBP_GameOver criado com sucesso
    ? Configure manualmente: UI Layout, Botões, Events

==> Salvando todos os assets...
    ? Assets salvos com sucesso

============================================================
? SETUP PYTHON CONCLUÍDO
============================================================
```

---

### Etapa 3: Configuração Manual (Seguir o Guia)

Após executar os scripts, você ainda precisa configurar manualmente:

**Consulte:** `ALPHA_VERSION_GUIDE_FIXED.md`

#### 3.1. Input Mapping Context (Seção 5.2)
- Abra `Content/ThirdPerson/Input/IMC_Default`
- Adicione mappings para `IA_Shoot` e `IA_Sprint`

#### 3.2. BP_Projectile (Seção 6.1)
- Adicione Static Mesh (Sphere)
- Configure Damage, Life Span
- Configure ProjectileMovement

#### 3.3. BP_PlayerCharacter (Seção 6.2)
- Configure Input Actions
- Configure Projectile Class
- Configure velocidades (Walk/Sprint)

#### 3.4. BP_BaseEnemy (Seção 7.1)
- Adicione Mesh
- Configure Health, Attack Damage
- Configure velocidades

#### 3.5. BP_EnemyAIController (Seção 7.2)
- Adicione lógica de "Move To Actor"
- Configure comportamento

#### 3.6. WBP_MainMenu (Seção 9.1)
- Design da UI (Title, Botões)
- Bind eventos dos botões

#### 3.7. WBP_GameOver (Seção 10.1)
- Design da UI
- Bind eventos dos botões

---

## ?? TROUBLESHOOTING

### Erro: "MSBuild não encontrado"
**Solução:**
- Instale Visual Studio 2022 (Community Edition)
- OU execute com `-SkipBuild` e compile manualmente

### Erro: "Classe C++ não encontrada" (Python)
**Solução:**
- Certifique-se de que o projeto foi compilado antes
- Execute o script PowerShell primeiro
- Regenere os project files: Clique direito em `.uproject` ? Generate Visual Studio project files

### Erro: "InputActionFactory não encontrado" (Python)
**Solução:**
- Este é um problema conhecido do UE5
- Crie os Input Actions manualmente no editor
- OU use o método de template (copiar IA_Jump e renomear)

### Erro: "Permissão negada" (PowerShell)
**Solução:**
- Execute o PowerShell como Administrador
- OU execute: `Set-ExecutionPolicy -Scope CurrentUser RemoteSigned`

### Assets não aparecem no Content Browser
**Solução:**
- Clique direito no Content Browser ? **Refresh**
- OU reinicie o editor

---

## ?? RESUMO DE AUTOMAÇÃO

| Tarefa | Automatização | Script | Manual |
|--------|---------------|--------|--------|
| **Validação** | ? 100% | PowerShell | 0% |
| **Pastas** | ? 100% | PowerShell | 0% |
| **Build Config** | ? 95% | PowerShell | 5% |
| **Compilação** | ? 90% | PowerShell | 10% |
| **Input Actions** | ?? 60% | Python | 40% |
| **Blueprints** | ?? 40% | Python | 60% |
| **Widgets** | ?? 30% | Python | 70% |
| **Configuração BP** | ? 0% | - | 100% |
| **UI Design** | ? 0% | - | 100% |
| **Level Design** | ? 0% | - | 100% |

**Total Geral:** ?? **~60% Automatizado**

---

## ?? ARQUIVOS RELACIONADOS

### Scripts
- `Tools/AlphaSetup.ps1` - Script PowerShell de automação
- `Content/Python/AlphaSetup.py` - Script Python para UE5 Editor

### Documentação
- `ALPHA_VERSION_GUIDE_FIXED.md` - Guia completo passo a passo
- `ALPHA_VERSION_GUIDE_CORRECTIONS.md` - Lista de correções aplicadas
- `AUTOMATION_ANALYSIS.md` - Análise detalhada de automação
- `SETUP_REPORT.md` - Relatório gerado após executar o script
- `AUTOMATION_README.md` - Este arquivo

### Gerados Automaticamente
- `SETUP_REPORT.md` - Gerado pelo script PowerShell
- `PtahStale.Build.cs.backup` - Backup do arquivo original

---

## ? CHECKLIST DE USO

- [ ] 1. Execute `.\Tools\AlphaSetup.ps1` (fora do editor)
- [ ] 2. Leia `SETUP_REPORT.md` gerado
- [ ] 3. Abra o projeto no UE5 Editor
- [ ] 4. Execute o script Python no Output Log
- [ ] 5. Verifique que os assets foram criados no Content Browser
- [ ] 6. Configure manualmente conforme `ALPHA_VERSION_GUIDE_FIXED.md`
- [ ] 7. Teste no `ThirdPersonMap`
- [ ] 8. ? Alpha Version pronta!

---

## ?? PRÓXIMOS PASSOS

Após concluir a automação:

1. **Configurar Blueprints** ? Seção 6-7 do guia
2. **Configurar UI** ? Seção 9-10 do guia
3. **Testar Gameplay** ? Seção 11 do guia
4. **Iterar e Melhorar** ? Feedback e ajustes

---

## ?? DICAS

- **Salve frequentemente:** Blueprints podem corromper se o editor crashar
- **Use controle de versão:** Commit após cada etapa concluída
- **Teste incrementalmente:** Não configure tudo de uma vez
- **Consulte os logs:** Output Log tem informações valiosas de debug

---

**Última Atualização:** 2024
**Versão:** 1.0
**Projeto:** PtahsTale Alpha Version
