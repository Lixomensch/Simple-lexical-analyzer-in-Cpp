import os
import subprocess

tests_dir = './tests'

output_dir = './tests/output'

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

def run_tests():
    for test_file in os.listdir(tests_dir):
        if test_file.endswith('.txt'):
            test_path = os.path.join(tests_dir, test_file)
            output_file = os.path.join(output_dir, f"{os.path.splitext(test_file)[0]}_output.txt")
            
            run_command = f"./lexer {test_path}"
            
            result = subprocess.run(run_command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            stdout_output = result.stdout.decode(errors='ignore')
            stderr_output = result.stderr.decode(errors='ignore')

            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(stdout_output)
                if stderr_output:
                    f.write(f"\nErros:\n{stderr_output}")

if __name__ == "__main__":
    run_tests()
    print("Testes executados e resultados salvos em 'tests/output'.")
