#include "DataGenerator.h"
#include "Student.h"
#include <random>
#include <cmath>


int generateRandomNumber(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

double generateRandomDouble(int min, int max, int accuracy)
{
    int factor = (int)pow(10, accuracy);
    int minScaled = min * factor;
    int maxScaled = max * factor;
    return generateRandomNumber(minScaled, maxScaled) / pow(10.0, accuracy);
}

void generateRandomArray(int *arr, int size, int min, int max)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = generateRandomNumber(min, max);
    }
}

std::vector<std::string> maleNames = {
    "Alexey", "Ivan", "Dmitry", "Nikita", "Maxim", "Artem", "Vladimir", "Oleg", "Konstantin", "Roman",
    "Sergey", "Daniil", "Georgiy", "Yegor", "Anatoly", "Vyacheslav", "Pyotr", "Vasily", "Mikhail", "Timofey"};

std::vector<std::string> femaleNames = {
    "Ekaterina", "Maria", "Sophia", "Anna", "Olga", "Anastasia", "Irina", "Tatyana", "Elena", "Darya",
    "Victoria", "Evgenia", "Polina", "Yulia", "Alena", "Natalya", "Nina", "Lyudmila", "Larisa", "Zoya"};

std::vector<std::string> surnames = {
    "Smirnov", "Ivanov", "Kuznetsov", "Sokolov", "Popov", "Lebedev", "Kozlov", "Novikov", "Morozov", "Petrov",
    "Volkov", "Solovyov", "Vasiliev", "Zaytsev", "Pavlov", "Semenov", "Golubev", "Vinogradov", "Bogdanov",
    "Vorobyov", "Fyodorov", "Mikhailov", "Belyaev", "Tarasov", "Belov", "Komarov", "Orlov", "Kiselyov", "Makarov",
    "Andreev", "Kovalev", "Ilyin", "Gusev", "Titov", "Kuzmin", "Kudryavtsev", "Baranov", "Kulikov", "Alexeev",
    "Stepanov", "Yakoblev", "Sorokin", "Sergeev", "Romanov", "Zakharov", "Borisov", "Korolev", "Gerasimov",
    "Ponomaryov", "Grigoryev", "Lazarev", "Medvedev", "Ershov", "Nikitin", "Sobolev", "Ryabov", "Polyakov",
    "Tsvetkov", "Danilov", "Zhukov", "Frolov", "Zhuravlyov", "Nikolaev", "Krylov", "Maximov", "Sidorov", "Osipov",
    "Belozuyov", "Fedotov", "Dorofeev", "Yegorov", "Matveev", "Bobrov", "Dmitriev", "Kalinin", "Anisimov",
    "Petukhov", "Antonov", "Timofeev", "Nikiforov", "Veselov", "Filippov", "Markov", "Bolshakov", "Sukhanov",
    "Mironov", "Shiryayev", "Alexandrov", "Konovalov", "Shestakov", "Kazakov", "Efimov", "Denisov", "Gromov",
    "Fomin", "Davydov", "Melnikov", "Shcherbakov", "Blinov", "Kolesnikov", "Karpev", "Afanasyev", "Vlasov",
    "Maslov", "Isakov", "Tikhonov", "Aksyonov", "Gavrilov", "Rodionov", "Kotov", "Gorbunov", "Kudryashov", "Bykov",
    "Zuev", "Tretyakov", "Saveliev", "Panov", "Rybakov", "Suvorov", "Abramov", "Voronov", "Mukhin", "Arhipov",
    "Trofimov", "Martynov", "Emelyanov", "Gorshkov", "Chernov", "Ovchinnikov", "Seleznev", "Panfilov", "Kopylov",
    "Mikheev", "Galkin", "Nazrov", "Lobanov", "Lukin", "Belyakov", "Potapov", "Nikrasov", "Khokhlov", "Zhdanov",
    "Naumov", "Shilov", "Vorontsov", "Ermakov", "Drozdov", "Ignatyev", "Savin", "Loginov", "Safonov", "Kapustin",
    "Kirillov", "Moiseev", "Yeliseev", "Koshelev", "Kostin", "Gorbachev", "Orekhov", "Efremov", "Isayev",
    "Evdokimov", "Kalashnikov", "Kabanov", "Noskov", "Yudin", "Kulagin", "Lapin", "Prokhorov", "Nesterov",
    "Kharitonov", "Agafonov", "Muravyov", "Laryonov", "Fedoseev", "Zimin", "Pakhomov", "Shubin", "Ignatov",
    "Filatov", "Kryukov", "Rogov", "Kulakov", "Terentyev", "Molchanov", "Vladimirov", "Artemyev", "Guryev",
    "Zinovyev", "Grishin", "Kononov", "Dementyev", "Sitnikov", "Simonov", "Mishin", "Fadeev", "Komissarov",
    "Mamonov", "Nosov", "Gulyaev", "Sharov", "Ustinov", "Vishnyakov", "Yevseev", "Lavrentyev", "Bragin",
    "Konstantinov", "Kornilov", "Avdeev", "Zykov", "Biryukov", "Sharapov", "Nikonomov", "Shchukin", "Dyachkov",
    "Odintsov", "Sazonov", "Yakushev", "Krasilnikov", "Gordeyev", "Samoylov", "Knyazev", "Bespalov", "Uvarov",
    "Shashkov", "Bobylev", "Doronin", "Belozyorov", "Roshkov", "Samsonov", "Myasnikov", "Likhachev", "Burov",
    "Sysoev", "Fomichev", "Rusakov", "Strelkov", "Gushchin", "Teterin", "Kolobov", "Subbotin", "Fokin", "Blokhin",
    "Seliverstov", "Pestov", "Kondratiev", "Silin", "Merkushev", "Lytkin", "Turov"};

Student generateStudent()
{
    int age = generateRandomNumber(17, 30);
    int course = generateRandomNumber(1, 4);
    double marks = generateRandomDouble(3, 5, 2);
    std::string name;
    std::string surname = surnames[generateRandomNumber(0, (int)surnames.size() - 1)];
    bool isFemale = generateRandomNumber(0, 1) == 0;
    if (isFemale)
    {
        name = femaleNames[generateRandomNumber(0, (int)femaleNames.size() - 1)];
        surname += "a";
    }
    else
    {
        name = maleNames[generateRandomNumber(0, (int)maleNames.size() - 1)];
    }
    return Student(name, surname, course, age, marks);
}

void generateStudentArray(Student *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = generateStudent();
    }
}

SharedPtr<Sequence<Student>> generateStudentSequence(int size)
{
    SharedPtr<Sequence<Student>> newSequence(new ListSequence<Student>());

    for (int i = 0; i < size; ++i) {
        newSequence->append( generateStudent());
    }
    return newSequence;
}

SharedPtr<Sequence<int>> generateIntegerSequence(int size, int min, int max) {
    SharedPtr<Sequence<int>> newSequence(new ListSequence<int>());

    for (int i = 0; i < size; ++i) {
        newSequence->append(generateRandomNumber(min, max));
    }
    return newSequence;
}


void writeStudentSequenceToFile(SharedPtr<Sequence<Student>> seq, const std::string &filename) {
    std::filesystem::path static_dir = "static";
    std::cout << static_dir << std::endl;

    if (!std::filesystem::exists(static_dir)) {
        std::filesystem::create_directory(static_dir);
    }

    std::filesystem::path filepath = static_dir / filename;

    std::ofstream ofs;
    ofs.open(filepath);
    if (!ofs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }

    for (int i = 0; i < seq->getLength(); i++)
    {
        Student s = seq->get(i);
        ofs <<
            "Name : " << s.getName() << " " << s.getSurname() <<
            " Age: " << s.getAge() <<
                " Score: "  << s.getAverageScore() <<
                    " Course: " << s.getCourse() << " \n";
    }

    ofs.close();
}

SharedPtr<Sequence<Student>> readStudentSequenceFromFile(const std::string &filename) {
    std::filesystem::path static_dir = "static";
    std::cout << "Reading from directory: " << static_dir << std::endl;

    // Ensure the static directory exists
    if (!std::filesystem::exists(static_dir)) {
        std::filesystem::create_directory(static_dir);
    }

    // Create the full file path
    std::filesystem::path filepath = static_dir / filename;

    // Open the file
    std::ifstream ifs(filepath);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file: " + filepath.string());
    }

    // Create a new sequence for the students
    SharedPtr<Sequence<Student>> newSequence(new ListSequence<Student>());

    // Read and parse the file line by line
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        std::string buffer, name, surname, ageLabel, scoreLabel, courseLabel;
        int age, course;
        double score;
        iss >> buffer >> buffer >> name >> surname >>  buffer >> ageLabel >>   buffer >> scoreLabel >> buffer >> courseLabel >> buffer;
        std::istringstream ( ageLabel ) >> age;
        std::istringstream ( scoreLabel ) >> score;
        std::istringstream ( courseLabel ) >> course;
        Student student(name, surname, course, age, score);
        newSequence->append(student);
    }

    // Close the file
    ifs.close();

    return newSequence;
}
