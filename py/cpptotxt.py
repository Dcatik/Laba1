import os

def analyze_folder_and_save(directory, output_file):
    # Открываем файл для записи
    with open(output_file, 'w', encoding='utf-8', errors = 'replace') as outfile:
        # Проходим по всем файлам и папкам в указанной директории
        for root, dirs, files in os.walk(directory):
            for file in files:
                # Ищем файлы с расширением .cpp и .h
                if file.endswith('.cpp') or file.endswith('.h'):
                    file_path = os.path.join(root, file)
                    # Записываем имя файла перед его содержимым
                    outfile.write(f'// {file}\n\n')
                    try:
                        # Открываем файл для чтения
                        with open(file_path, 'r', encoding='ISO-8859-1') as infile:
                            # Читаем и записываем содержимое файла
                            outfile.write(infile.read())
                            outfile.write('\n\n')  # Добавляем разделитель между файлами
                    except Exception as e:
                        print(f"Ошибка при чтении файла {file_path}: {e}")

if __name__ == '__main__':
    # Указываем папку для анализа и имя выходного файла
    directory_to_analyze = '../Laba1/'  # Замените на нужный путь
    output_txt_file = 'output.txt'
    analyze_folder_and_save(directory_to_analyze, output_txt_file)
