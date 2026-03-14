# =====================================================
# PTAHSTALE - ALPHA VERSION SETUP AUTOMATION
# =====================================================
# Este script automatiza a configuração inicial do projeto
# para a versão Alpha jogável
# =====================================================

param(
    [switch]$SkipBuild,
    [switch]$ValidateOnly,
    [switch]$Verbose
)

$ErrorActionPreference = "Stop"
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$ProjectName = "PtahsTale"

# =====================================================
# FUNÇÕES AUXILIARES
# =====================================================

function Write-Step {
    param([string]$Message)
    Write-Host "`n==> $Message" -ForegroundColor Cyan
}

function Write-Success {
    param([string]$Message)
    Write-Host "    ? $Message" -ForegroundColor Green
}

function Write-Warning {
    param([string]$Message)
    Write-Host "    ? $Message" -ForegroundColor Yellow
}

function Write-Error {
    param([string]$Message)
    Write-Host "    ? $Message" -ForegroundColor Red
}

function Test-FileExists {
    param([string]$Path, [string]$Description)
    if (Test-Path $Path) {
        Write-Success "$Description encontrado"
        return $true
    } else {
        Write-Warning "$Description não encontrado: $Path"
        return $false
    }
}

# =====================================================
# VALIDAÇÃO DE ESTRUTURA
# =====================================================

function Test-ProjectStructure {
    Write-Step "Validando estrutura do projeto..."
    
    $required = @{
        "Source/$ProjectName" = "Pasta de código fonte"
        "Content" = "Pasta de conteúdo"
        "$ProjectName.uproject" = "Arquivo de projeto UE"
    }
    
    $allValid = $true
    foreach ($path in $required.Keys) {
        $fullPath = Join-Path $ProjectRoot $path
        if (-not (Test-FileExists $fullPath $required[$path])) {
            $allValid = $false
        }
    }
    
    return $allValid
}

function Test-CppFiles {
    Write-Step "Validando arquivos C++ necessários..."
    
    $sourceDir = Join-Path $ProjectRoot "Source\$ProjectName"
    
    $requiredFiles = @(
        "Combat\HealthComponent.h",
        "Combat\HealthComponent.cpp",
        "Combat\Projectile.h",
        "Combat\Projectile.cpp",
        "Combat\CombatComponent.h",
        "Combat\ParasiteEnergyComponent.h",
        "Combat\ParasiteEnergyComponent.cpp",
        "Enemies\BaseEnemy.h",
        "Enemies\BaseEnemy.cpp",
        "Inventory\InventoryComponent.h",
        "Inventory\InventoryComponent.cpp",
        "Data\ItemData.h",
        "Data\ItemData.cpp",
        "Data\WeaponData.h",
        "Data\WeaponData.cpp",
        "Data\ArmorData.h",
        "Data\ArmorData.cpp",
        "PtahStaleCharacter.h",
        "PtahStaleCharacter.cpp",
        "PtahStaleGameMode.h",
        "PtahStaleGameMode.cpp"
    )
    
    $allValid = $true
    foreach ($file in $requiredFiles) {
        $fullPath = Join-Path $sourceDir $file
        if (-not (Test-FileExists $fullPath $file)) {
            $allValid = $false
        }
    }
    
    return $allValid
}

function Test-ContentStructure {
    Write-Step "Validando estrutura de Content..."
    
    $contentDir = Join-Path $ProjectRoot "Content"
    
    $existingPaths = @{
        "ThirdPerson\Input\Actions" = "Input Actions existentes"
        "ThirdPerson\Input" = "Input Mapping Context"
        "ThirdPerson\Blueprints" = "Blueprints ThirdPerson"
        "ThirdPerson\Maps" = "Maps ThirdPerson"
    }
    
    $allValid = $true
    foreach ($path in $existingPaths.Keys) {
        $fullPath = Join-Path $contentDir $path
        if (-not (Test-FileExists $fullPath $existingPaths[$path])) {
            $allValid = $false
        }
    }
    
    return $allValid
}

function New-RequiredFolders {
    Write-Step "Criando pastas necessárias..."
    
    $contentDir = Join-Path $ProjectRoot "Content"
    
    $foldersToCreate = @(
        "Blueprints\Combat",
        "Blueprints\Player",
        "Blueprints\Enemies",
        "Blueprints\AI",
        "Blueprints\Procedural",
        "UI",
        "Maps"
    )
    
    foreach ($folder in $foldersToCreate) {
        $fullPath = Join-Path $contentDir $folder
        if (-not (Test-Path $fullPath)) {
            New-Item -Path $fullPath -ItemType Directory -Force | Out-Null
            Write-Success "Criada: $folder"
        } else {
            Write-Success "Já existe: $folder"
        }
    }
}

# =====================================================
# CONFIGURAÇÃO DE BUILD
# =====================================================

function Update-BuildConfiguration {
    Write-Step "Atualizando configuração de build..."
    
    $buildFile = Join-Path $ProjectRoot "Source\$ProjectName\PtahStale.Build.cs"
    
    if (-not (Test-Path $buildFile)) {
        Write-Error "Arquivo PtahStale.Build.cs não encontrado"
        return $false
    }
    
    # Ler conteúdo atual
    $content = Get-Content $buildFile -Raw
    
    # Verificar se já está configurado
    if ($content -match "NavigationSystem" -and $content -match "UMG") {
        Write-Success "Build.cs já está configurado corretamente"
        return $true
    }
    
    # Backup
    $backupFile = "$buildFile.backup"
    Copy-Item $buildFile $backupFile -Force
    Write-Success "Backup criado: $backupFile"
    
    # Atualizar módulos
    $newModules = @"
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
"@
    
    # Substituir seção de módulos
    $pattern = "PublicDependencyModuleNames\.AddRange.*?}\s*\);"
    if ($content -match $pattern) {
        $content = $content -replace $pattern, $newModules
        Set-Content $buildFile -Value $content -Encoding UTF8
        Write-Success "Build.cs atualizado com sucesso"
        return $true
    } else {
        Write-Warning "Não foi possível atualizar automaticamente. Faça manualmente."
        return $false
    }
}

# =====================================================
# COMPILAÇÃO
# =====================================================

function Invoke-ProjectBuild {
    Write-Step "Compilando projeto..."
    
    # Procurar MSBuild
    $msbuildPaths = @(
        "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe",
        "C:\Program Files\Microsoft Visual Studio\2022\Professional\MSBuild\Current\Bin\MSBuild.exe",
        "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\MSBuild\Current\Bin\MSBuild.exe",
        "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
    )
    
    $msbuild = $null
    foreach ($path in $msbuildPaths) {
        if (Test-Path $path) {
            $msbuild = $path
            break
        }
    }
    
    if (-not $msbuild) {
        Write-Warning "MSBuild não encontrado. Compile manualmente no Visual Studio."
        return $false
    }
    
    Write-Success "MSBuild encontrado: $msbuild"
    
    $solutionFile = Join-Path $ProjectRoot "$ProjectName.sln"
    
    if (-not (Test-Path $solutionFile)) {
        Write-Warning "Arquivo .sln não encontrado. Execute 'Generate Visual Studio project files' primeiro."
        return $false
    }
    
    Write-Host "    Compilando (isso pode demorar alguns minutos)..."
    
    $buildArgs = @(
        "`"$solutionFile`"",
        "/t:Build",
        "/p:Configuration=Development",
        "/p:Platform=Win64",
        "/m",
        "/v:minimal"
    )
    
    try {
        $process = Start-Process -FilePath $msbuild -ArgumentList $buildArgs -NoNewWindow -Wait -PassThru
        
        if ($process.ExitCode -eq 0) {
            Write-Success "Compilação concluída com sucesso!"
            return $true
        } else {
            Write-Error "Compilação falhou. Verifique os erros no Visual Studio."
            return $false
        }
    } catch {
        Write-Error "Erro ao compilar: $_"
        return $false
    }
}

# =====================================================
# RELATÓRIO
# =====================================================

function New-SetupReport {
    Write-Step "Gerando relatório de setup..."
    
    $reportPath = Join-Path $ProjectRoot "SETUP_REPORT.md"
    
    $report = @"
# RELATÓRIO DE SETUP - PTAHSTALE ALPHA

**Data:** $(Get-Date -Format "yyyy-MM-dd HH:mm:ss")

---

## ? CONFIGURAÇÃO AUTOMÁTICA CONCLUÍDA

### Estrutura de Pastas Criadas
- ? Content/Blueprints/Combat
- ? Content/Blueprints/Player
- ? Content/Blueprints/Enemies
- ? Content/Blueprints/AI
- ? Content/Blueprints/Procedural
- ? Content/UI
- ? Content/Maps

### Arquivos C++ Validados
- ? HealthComponent
- ? Projectile
- ? BaseEnemy
- ? CombatComponent
- ? ParasiteEnergyComponent
- ? InventoryComponent
- ? ItemData/WeaponData/ArmorData

### Build Configuration
- ? PtahStale.Build.cs atualizado
- ? Módulos necessários adicionados (UMG, AIModule, NavigationSystem, etc)

---

## ?? PRÓXIMOS PASSOS MANUAIS

### 1. Abrir o Editor UE5
1. Abra o arquivo ``PtahsTale.uproject``
2. Aguarde o editor carregar

### 2. Criar Input Actions Faltantes
No Content Browser, navegue para ``Content/ThirdPerson/Input/Actions/``:
1. Criar ``IA_Shoot`` (Digital/bool)
2. Criar ``IA_Sprint`` (Digital/bool)

### 3. Atualizar Input Mapping Context
Abra ``Content/ThirdPerson/Input/IMC_Default``:
1. Adicionar mapping: ``IA_Shoot`` ? Left Mouse Button
2. Adicionar mapping: ``IA_Sprint`` ? Left Shift
3. Salvar

### 4. Executar Script Python (Opcional - Cria Blueprints base)
No Editor UE5:
1. Window ? Developer Tools ? Output Log
2. Aba "Python"
3. Executar: ``exec(open('Content/Python/AlphaSetup.py').read())``

### 5. Configurar Blueprints Manualmente
Consulte o arquivo ``ALPHA_VERSION_GUIDE_FIXED.md`` para instruções detalhadas:
- BP_Projectile (seção 6.1)
- BP_PlayerCharacter (seção 6.2)
- BP_BaseEnemy (seção 7.1)
- BP_EnemyAIController (seção 7.2)
- WBP_MainMenu (seção 9.1)
- WBP_GameOver (seção 10.1)

### 6. Testar o Jogo
1. Abra ``Content/ThirdPerson/Maps/ThirdPersonMap``
2. Pressione Play (Alt+P)
3. Teste movimento, pulo, câmera

---

## ?? DOCUMENTAÇÃO

- **Guia Completo:** ``ALPHA_VERSION_GUIDE_FIXED.md``
- **Correções Aplicadas:** ``ALPHA_VERSION_GUIDE_CORRECTIONS.md``
- **Análise de Automação:** ``AUTOMATION_ANALYSIS.md``
- **Este Relatório:** ``SETUP_REPORT.md``

---

## ?? TROUBLESHOOTING

### Erro de Compilação
Se houver erros ao compilar:
1. Feche o Visual Studio
2. Clique direito em ``PtahsTale.uproject``
3. Selecione "Generate Visual Studio project files"
4. Abra novamente e compile

### Assets não aparecem no Editor
1. Verifique se as pastas foram criadas em ``Content/``
2. Clique direito no Content Browser ? "Show in Explorer"
3. Verifique se os arquivos estão na pasta correta

### Input não funciona
1. Verifique se ``IA_Shoot`` e ``IA_Sprint`` foram criados
2. Verifique se ``IMC_Default`` está configurado
3. Verifique se o Character Blueprint está usando ``IMC_Default``

---

**Script executado por:** ``Tools/AlphaSetup.ps1``
"@
    
    Set-Content $reportPath -Value $report -Encoding UTF8
    Write-Success "Relatório salvo em: SETUP_REPORT.md"
}

# =====================================================
# MAIN
# =====================================================

function Start-AlphaSetup {
    Write-Host @"

?????????????????????????????????????????????????????????
?  PTAHSTALE - ALPHA VERSION SETUP AUTOMATION         ?
?  Automação de configuração inicial                   ?
?????????????????????????????????????????????????????????

"@ -ForegroundColor Cyan

    # Validação
    $valid = $true
    $valid = $valid -and (Test-ProjectStructure)
    $valid = $valid -and (Test-CppFiles)
    $valid = $valid -and (Test-ContentStructure)
    
    if (-not $valid) {
        Write-Error "`nValidação falhou. Verifique os problemas acima."
        return
    }
    
    if ($ValidateOnly) {
        Write-Success "`n? Validação concluída com sucesso!"
        return
    }
    
    # Criar pastas
    New-RequiredFolders
    
    # Atualizar build config
    Update-BuildConfiguration
    
    # Compilar (se solicitado)
    if (-not $SkipBuild) {
        $buildSuccess = Invoke-ProjectBuild
        if (-not $buildSuccess) {
            Write-Warning "Compilação falhou ou foi pulada. Continue manualmente."
        }
    } else {
        Write-Warning "Compilação pulada (-SkipBuild). Compile manualmente."
    }
    
    # Gerar relatório
    New-SetupReport
    
    Write-Host @"

?????????????????????????????????????????????????????????
?  ? SETUP AUTOMÁTICO CONCLUÍDO                       ?
?????????????????????????????????????????????????????????

?? Próximos passos:
   1. Leia o arquivo SETUP_REPORT.md
   2. Abra o editor UE5
   3. Execute o script Python (opcional)
   4. Configure os Blueprints conforme o guia

?? Documentação completa em: ALPHA_VERSION_GUIDE_FIXED.md

"@ -ForegroundColor Green
}

# Executar
Start-AlphaSetup
