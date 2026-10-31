//CONTACT MANAGER
#include<string>
#include<iostream>
#include<limits>
#include<vector>
#include<stdexcept>
#include<fstream>
#include <sstream>


// Cria os contatos da agenda
class Contato
{
private:
	std::string nome;
	std::string dataNascimento;
	std::string telefone;
	std::string email;

public:

	Contato(std::string nome,
		std::string dataNascimento,
		std::string telefone = "",
		std::string email = "")

		:nome(nome),
		dataNascimento(dataNascimento),
		telefone(telefone),
		email(email)

		//Construtor da classe Contato
	{
		if (nome.empty() || nome.find(';') != std::string::npos)
		{
			throw std::invalid_argument(
				"Nome nao pode ser vazio nem conter ';'."
			);
		}

		if (dataNascimento.empty() || dataNascimento.find(';') != std::string::npos)
		{
			throw std::invalid_argument(
				"Data de nascimento nao pode ser vazia nem conter ';'."
			);
		}

		if (telefone.find(';') != std::string::npos)
		{
			throw std::invalid_argument(
				"Telefone nao pode conter ';'."
			);
		}

		if (email.find(';') != std::string::npos)
		{
			throw std::invalid_argument(
				"Email nao pode conter ';'."
			);
		}
		
	}


	std::string getNome() const
	{
		return nome;
	}

	std::string getDataNascimento() const
	{
		return dataNascimento;
	}

	std::string getTelefone() const
	{
		return telefone;
	}

	std::string getEmail() const
	{
		return email;
	}

	bool setNome(std::string novoNome)
	{
    if (novoNome.empty() ||
        novoNome.find(';') != std::string::npos)
    {
        std::cout << "Nome nao pode ser vazio nem conter ';'."
                  << std::endl;
        return false;
    }

		nome = novoNome;
		return true;
	}
	

	bool setDataNascimento(std::string novaDataNascimento)
	{
		if (novaDataNascimento.empty() ||
			novaDataNascimento.find(';') != std::string::npos)
		{
			std::cout << "A data nao pode ser vazia nem conter ';'."
				<< std::endl;
			return false;
		}
		dataNascimento = novaDataNascimento;
		return true;
	}
	

	bool setTelefone(std::string novoTelefone)
	{
		if (novoTelefone.find(';') != std::string::npos)
		{
			std::cout << "O telefone nao pode conter ';'."
				<< std::endl;
			return false;
		}
		telefone = novoTelefone;
		return true;
	}

	bool setEmail(std::string novoEmail)
	{
		if (novoEmail.find(';') != std::string::npos)
		{
			std::cout << "O email nao pode conter ';'."
				<< std::endl;
			return false;
		}		
		email = novoEmail;
		return true;
	}
	
};
// Gerencia os contatos da agenda
class GerenciadorDeContatos
{
private:

	std::vector<Contato> contatos;

public:

	void criarContato() {

		std::string nome;
		std::string dataNascimento;
		std::string telefone;
		std::string email;

		std::cout << " CRIAR CONTATO " << std::endl;

		while (true) {
			std::cout << " Digite o Nome: " << std::endl;
			std::getline(std::cin, nome);
			if (!nome.empty() && nome.find(';') == std::string::npos) {
				break;
			}
			std::cout << "Nome nao pode ser vazio e nao pode conter ';'. Tente novamente." << std::endl;
		}

		while (true) {
			std::cout << " Digite a Data de Nascimento: " << std::endl;
			std::getline(std::cin, dataNascimento);
			if (!dataNascimento.empty() && dataNascimento.find(';') == std::string::npos) 
			{
				break;
			}
			std::cout << "Data de nascimento nao pode ser vazia e nao pode conter ';'. Tente novamente." 
				<< std::endl;
		}
	
		while (true) {
			std::cout << " Digite o Telefone: " << std::endl;
			std::getline(std::cin, telefone);
			if (telefone.find(';') == std::string::npos)
			{
				break;
			}
			std::cout << "Nao pode conter ';'. Tente novamente."
				<< std::endl;
		}

		while (true) {
			std::cout << " Digite o email: " << std::endl;
			std::getline(std::cin, email);
			if (email.find(';') == std::string::npos)
			{
				break;
			}
			std::cout << "Email nao pode conter ';'. Tente novamente."
				<< std::endl;
		}


			try
		{
			Contato novoContato(
				nome,
				dataNascimento,
				telefone,
				email
			);

			contatos.push_back(novoContato);
			salvarContatos();
					

			/* Exibe a quantidade de contatos e a capacidade do vetor (uso didático, não incluir em documentação oficial)
			std::cout << "Quantidade: " << contatos.size() << '\n';
			std::cout << "Capacidade: " << contatos.capacity() << '\n';*/

		}
		catch (const std::invalid_argument& erro)
		{
			std::cout << erro.what() << std::endl;
		}
	}

	void listarContatos() const
	{
		if (contatos.empty()) {
			std::cout << "Nenhum contato cadastrado." << std::endl;
			return;
		}

		std::cout << "LISTAR CONTATOS" << std::endl;

		for (std::size_t i = 0; i < contatos.size(); i++)
		{
			int indice = i + 1;
			std::cout << " **** CONTATO " << indice << " ****" << std::endl;
			std::cout << "Nome: " << contatos[i].getNome() << std::endl;
			std::cout << "Data de Nascimento: " << contatos[i].getDataNascimento() << std::endl;
			std::cout << "Telefone: " << contatos[i].getTelefone() << std::endl;
			std::cout << "Email: " << contatos[i].getEmail() << std::endl;

		}
		std::cout << "------------------------------- " << std::endl;
	}

	void buscarContato()
	{

		std::string nomeProcurado{};
		

		std::cout << "Digite o nome procurado: " << std::endl;
		std::getline(std::cin, nomeProcurado);

		Contato* contatoEncontrado = encontrarContato(nomeProcurado);

		if (contatoEncontrado != nullptr) {
			std::cout << "Contato encontrado!" << std::endl;
			std::cout << "Nome: " << contatoEncontrado->getNome() << std::endl;
			std::cout << "Data de Nascimento: " << contatoEncontrado->getDataNascimento() << std::endl;
			std::cout << "Telefone: " << contatoEncontrado->getTelefone() << std::endl;
			std::cout << "Email: " << contatoEncontrado->getEmail() << std::endl;
		}
		else {
			std::cout << "Contato não encontrado!" << std::endl;
		}
		
				
	}

	Contato* encontrarContato(std::string nome)
	{
		
		for (std::size_t i = 0; i < contatos.size(); i++)
		{

			if (contatos[i].getNome() == nome) {
				return &contatos[i];
			}
		}
		return nullptr;
			
	}

	void atualizarContato()
	{
		std::string nomeProcurado{};
		std::cout << "Digite o nome do Contato para atualizar: " << std::endl;
		std::getline(std::cin, nomeProcurado);

		Contato* contatoEncontrado = encontrarContato(nomeProcurado);

		if (contatoEncontrado != nullptr) {
			std::cout << "Contato encontrado!" << std::endl;

			while (true) {
				std::cout << "Escolha o campo para atualizar:\n1. Nome\n2. Data de Nascimento\n3. Telefone\n4. Email\n0. Sair" << std::endl;
				int opcao{};
				std::cin >> opcao;
				if (std::cin.fail())
				{
					std::cout << "ERRO DE ENTRADA!" << std::endl;
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				switch (opcao) {
				case 1:
				{
					std::string novoNome;

					while (true)
					{
						std::cout << "Atualizar nome:" << std::endl;
						std::getline(std::cin, novoNome);

						//std::cout << "[DEBUG] Nome recebido: [" << novoNome << "]" << std::endl;

						if (!novoNome.empty() && novoNome.find(';') == std::string::npos)
						{
							break;
						}
										
						std::cout << "Nome nao pode ser vazio e nao pode conter ';'. Tente novamente." 
							<< std::endl;
					}

					if (contatoEncontrado->setNome(novoNome))
					{
						salvarContatos();
					}
					break;

				}
				case 2:
				{
					std::string novaData;

					while (true)
					{

					std::cout << "Atualizar data de nascimento" << std::endl;
					std::getline(std::cin, novaData);

					if (!novaData.empty() && novaData.find(';') == std::string::npos)
					{
						break;
					}

					std::cout << "Data de nascimento nao pode ser vazia e nao pode conter ';'. Tente novamente." << std::endl;
					
					}		

					if (contatoEncontrado->setDataNascimento(novaData))
					{
						salvarContatos();
					}
					break;
				}

				case 3:
				{
					std::string novoTelefone;

					while (true)
					{

					std::cout << "Atualizar telefone" << std::endl;
					std::getline(std::cin, novoTelefone);

					if (novoTelefone.find(';') == std::string::npos)
					{
						break;
					}

					std::cout << "Nao pode conter ';'. Tente novamente." << std::endl;

					}

					if (contatoEncontrado->setTelefone(novoTelefone))
					{
						salvarContatos();
					}
					break;
				}
				case 4:
				{
					std::string novoEmail;

					while (true)
					{

						std::cout << "Atualizar email" << std::endl;
						std::getline(std::cin, novoEmail);

						if (novoEmail.find(';') == std::string::npos)
						{
							break;
						}

						std::cout << "Nao pode conter ';'. Tente novamente." << std::endl;

					}
					
					if (contatoEncontrado->setEmail(novoEmail))
					{
						if (salvarContatos()){

							std::cout << "Contato atualizado e salvo com sucesso!" << std::endl;
						}
						else {
							std::cout << "Contato atualizado na memoria,"
								<< " mas nao foi salvo no arquivo." 
								<< std::endl;
						
						}
					}
					break;
				}

				case 0:
					return;
				default:
					std::cout << "Opcao invalida. Tente novamente." << std::endl;
				}
			}
			
		}
		else {
			std::cout << "Contato não encontrado!" << std::endl;
		}

	}

	void removerContato()
	{
		if (contatos.empty())
		{
			std::cout << "Nenhum contato cadastrado." << std::endl;
			return;
		}
	

		std::string nomeProcurado{};

		std::cout << "Digite o nome do Contato para remover: " << std::endl;
		std::getline(std::cin, nomeProcurado);

		Contato* contatoEncontrado = encontrarContato(nomeProcurado);

		if (contatoEncontrado == nullptr) {

			std::cout << "Contato não encontrado!" << std::endl;
			return;
		}
		std::size_t indice = contatoEncontrado - &contatos[0];

				contatos.erase(contatos.begin() + indice);
				std::cout << "Contato removido com sucesso!" << std::endl;
				salvarContatos();
	}	

	bool salvarContatos() const
	{
		std::ofstream arquivo("contatos.txt");
		if (!arquivo.is_open()) {
			std::cout << "Erro ao abrir o arquivo." << std::endl;
			return false;
		}
		for (const Contato& contato : contatos)
		{
			arquivo << contato.getNome() << ";"
				<< contato.getDataNascimento() << ";"
				<< contato.getTelefone() << ";"
				<< contato.getEmail() << "\n";
		}

		arquivo.close();
		
		if (!arquivo) {
				std::cout << "Erro durante a gravação ou fechamento do arquivo." << std::endl;
				return false;
		}
		return true;

	}

	void carregarContatos()
	{
		std::ifstream arquivo("contatos.txt");

		if (!arquivo.is_open()) {
			std::cout << "Erro ao abrir o arquivo, ou arquivo não encontrado." << std::endl;
			return;
		}
		std::string linha;
		std::size_t numeroDaLinha = 0;

		while (std::getline(arquivo, linha)) {
			++numeroDaLinha;

			const auto primeiro = linha.find(';');
			const auto segundo = primeiro == std::string::npos
				? std::string::npos : linha.find(';', primeiro + 1);
			const auto terceiro = segundo == std::string::npos
				? std::string::npos : linha.find(';', segundo + 1);

			if (terceiro == std::string::npos ||
				linha.find(';', terceiro + 1) != std::string::npos) {
				std::cout << "Linha " << numeroDaLinha
					<< " invalida: esperado nome;data;telefone;email.\n";
				continue;
			}

			std::string nome = linha.substr(0, primeiro);
			std::string dataNascimento =
				linha.substr(primeiro + 1, segundo - primeiro - 1);
			std::string telefone =
				linha.substr(segundo + 1, terceiro - segundo - 1);
			std::string email = linha.substr(terceiro + 1);

			try {
				contatos.emplace_back(nome, dataNascimento, telefone, email);
			}
			catch (const std::invalid_argument& erro) {
				std::cout << "Linha " << numeroDaLinha
					<< " invalida: " << erro.what() << '\n';
			}
		}
		}

};

	int main() {

		std::cout << "*** CONTACT MANAGER ***" << std::endl;
		std::cout << "Digite uma Opcao:" << std::endl;
						
		GerenciadorDeContatos gerenciador;
		gerenciador.carregarContatos();

		//Menu principal do programa, com as opcoes de criar, listar, buscar e atualizar contatos
		while (true) {
			std::cout << "\n1. Criar Contato\n2. Listar Contato\n3. Buscar Contato\n4. Atualizar Contato\n5. Remover Contato\n0. Sair\nOpcao: " << std::endl;
			int opcao{};
			std::cin >> opcao;
			if (std::cin.fail())
			{
				std::cout << "ERRO DE ENTRADA!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			switch (opcao) {
			case 1:
				gerenciador.criarContato();
				break;

			case 2:
				gerenciador.listarContatos();
				break;

			case 3:
				gerenciador.buscarContato();
				break;

			case 4:
				gerenciador.atualizarContato();
				break;

			case 5:
				gerenciador.removerContato();
				break;

			case 0:
				std::cout << "Saindo do Programa..." << std::endl;
				return 0;

			default:
				std::cout << "Opcao invalida. Tente novamente." << std::endl;
			}

		}
		
		return 0;
	}