// Djalma Ponciano Rodrigues
#include <stdio.h>
#include <stdlib.h>

#define arquivo "Alunos.dat"
FILE *pfile;

struct Aluno{
    int matricula;
    char nome[50];
    float nota;
};

void ConfirmaMatricula(char a, struct Aluno AddAluno){
    
    if(a == 'Y' || a == 'y'){
        fwrite(&AddAluno, sizeof(struct Aluno), 1, pfile);
        printf("\n======Aluno adicionado !!=====\n");
    }
    else if(a == 'N' || a == 'n'){
        printf("Tente novamente !");
    }
    else{
        printf("Erro");
    }
}

void AddAluno(){

    struct Aluno aluno;
    char confirmar;

    printf("De o codigo da matricula: ");
    scanf("%d", &aluno.matricula);

    printf("De o nome do aluno: ");
    scanf(" %[^\n]", aluno.nome);

    printf("De a nota do aluno: ");
    scanf("%f", &aluno.nota);

    printf("Deseja adicionar esse aluno ? (Y - sim / N - nao): ");
    scanf(" %c", &confirmar);

    pfile = fopen(arquivo, "ab");

    if(pfile != NULL){

        ConfirmaMatricula(confirmar, aluno);

        fclose(pfile);
    }
    else{
        printf("ERRO");
    }
}

void ListarAluno(){

    struct Aluno aluno;

    pfile = fopen(arquivo, "rb"); //Abre o arquivo para leitura que foi criado

    if(pfile != NULL){

        while(fread(&aluno, sizeof(struct Aluno), 1, pfile) == 1){

        printf("\nDADOS LIDOS:");
        printf("\nMatricula do aluno: %d\n", aluno.matricula);
        printf("Nome aluno: %s\n", aluno.nome);
        printf("Nota: %.2f\n", aluno.nota);

        }

        fclose(pfile); //fecha 
    }
    else{
        printf("Arquivo não encontrado");
    }
}

void BuscarAluno(){

    struct Aluno aluno;
    int matricula;

    pfile = fopen(arquivo, "rb");

    if(pfile != NULL){

        printf("====Buscar Alunos ====");
        printf("\nNumero da matricula: ");
        scanf("%d", &matricula);

        while(fread(&aluno, sizeof(struct Aluno), 1, pfile) == 1){

            if(matricula == aluno.matricula){
                printf("\nMatricula do aluno: %d\n", aluno.matricula);
                printf("Nome aluno: %s\n", aluno.nome);
                printf("Nota: %.2f\n", aluno.nota);
            }
        }
    }
    else{
        printf("Erro ao buscar os alunos");
    }
}

void RemoverAluno(){
    FILE *temp;
    struct Aluno aluno;
    int matriDelete, encontrado = 0;

    printf("Digite a matricula que deseja deletar: ");
    scanf("%d", &matriDelete);

    pfile = fopen(arquivo, "rb");

    if(!pfile){
        printf("Erro ao abrir o arquivo !!");
        return;
    }

    struct Aluno alvo;
    while(fread(&alvo, sizeof(struct Aluno), 1, pfile)){
        if(alvo.matricula == matriDelete){
            encontrado = 1;
            break;
        }
    }

    if(!encontrado){
        printf("Aluno nao encontrado !!\n");
        fclose(pfile);
        return;
    }

    // Exibir informações do aluno
    printf("\n=== ALUNO ENCONTRADO ===\n");
    printf("Matricula: %d\n", alvo.matricula);
    printf("Nome: %s\n", alvo.nome);
    printf("Nota: %.2f\n", alvo.nota);

    // Confirmação
    char resp;
    printf("\nDeseja realmente deletar este aluno? (S/N): ");
    scanf(" %c", &resp);

    if(resp != 'S' && resp != 's'){
        printf("Operacao cancelada!\n");
        fclose(pfile);
        return;
    }

    // Se confirmou, precisa voltar ao início do arquivo
    rewind(pfile);

    temp = fopen("Temp.dat", "wb");
    if(!temp){
        printf("Erro ao abrir o arquivo temporario !!");
        fclose(pfile);
        return;
    }

    // Copiar todos os alunos
    while(fread(&aluno, sizeof(struct Aluno), 1, pfile)){
        if(aluno.matricula != matriDelete){
            fwrite(&aluno, sizeof(struct Aluno), 1, temp);
        }
    }

    fclose(pfile);
    fclose(temp);

    // Substituir o arquivo original
    remove("Alunos.dat");
    rename("Temp.dat", "Alunos.dat");

    printf("\nAluno deletado com sucesso !!\n");
}

void Menu(){

    int escolha = 0;

    do{
        printf("\n===== MENU ====\n");
        printf("Escolha uma das opcoes abaixo:\n1 - Adicionar um aluno\n2 - Listar todos os alunos\n3 - Buscar um aluno\n4 - Deletar um aluno\n5 - Sair\nOpcao: ");

        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                AddAluno();
                break;

            case 2:
                ListarAluno();
                break;
            
            case 3:
                BuscarAluno();
                break;

            case 4:
                RemoverAluno();
                break;

            case 5:
                printf("Saindo ....");
                break;
        }
    } while (escolha != 5);
}

int main(){

    Menu();

    return 0;
}