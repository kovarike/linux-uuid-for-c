
# Winid

Esta biblioteca fornece funções para gerar UUIDs (Universally Unique Identifiers) em C. O objetivo é facilitar a criação e manipulação de UUIDs em suas aplicações.

## Exemplo de Uso

- **Geração de UUIDs**: Cria UUIDs usando a função `create_uuid()`.
- **Parsing de UUIDs**: Converte UUIDs para uma string formatada usando a função `parse()`.

### 1. Utilizando o `parse` para copiar o ID gerado para outra variável

O exemplo abaixo mostra como criar um UUID, usar a função `parse` para copiá-lo para a variável `userid`, e, em seguida, exibi-lo.

```c
#include <stdio.h>
#include <stdlib.h>
#include "uuid.h"  

int main() {
    char userid[37]; 

    Uuid *id = create_uuid(); 

    parse(userid, id); 
    
    printf("UUID gerado: %s\n", userid); 
  
    free(id); 
    return 0;
}
```

### 2. Neste exemplo, geramos um UUID e exibimos diretamente a string sem usar a função `parse()`.

```c
#include <stdio.h>
#include "uuid.h" 

int main() {
    Uuid *id = create_uuid(); 
    printf("UUID gerado: %s\n", id->uuid); 
  
    free(id); 
    return 0;
}

```

## Instalação

Para utilizar esta biblioteca, clone o repositório e inclua os arquivos da biblioteca no seu projeto.

```bash
git clone https://github.com/kovarike/win-uuid-for-c.git
```

<!-- ### Descrições adicionais

// - **Introdução**: Uma breve introdução ao que a biblioteca faz.
// - **Funcionalidades**: Uma seção para destacar as principais funções e características da biblioteca.
// - **Instalação**: Instruções sobre como instalar ou incluir a biblioteca no projeto.
// - **Exemplo de Uso**: Exemplos de código ilustrativos que mostram como usar as funções.
// - **Estrutura da Biblioteca**: Uma descrição da estrutura do projeto, incluindo os principais arquivos.
// - **Contribuição**: Informações sobre como contribuir com o projeto.
// - **Licença**: Detalhes sobre a licença sob a qual o projeto é disponibilizado. 

// Sinta-se à vontade para personalizar o conteúdo de acordo com suas necessidades! -->



