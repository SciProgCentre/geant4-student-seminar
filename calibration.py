import os, sys
import subprocess
from multiprocessing.pool import Pool
from string import Template

template = Template("""/mipt/mode gps
/mipt/field 0.0 kilogauss
/mipt/output ${output}
/gps/particle ${particle}
/gps/direction 0 0 1
/gps/ene/mono ${energy} MeV
/run/beamOn ${number}
""")


def generator():
    number = 50000 
    for particle in ["gamma", "e-"]:
        for energy in range(10, 70, 10):
            output = "{}_{}MeV_{}n".format(particle, energy, number)
            result = {
                'number': number,
                'energy': float(energy),
                'particle': particle,
                "output": output
            }
            yield result


def run(parameters: dict):
    pwd = os.getcwd()
    output_dir = "calibration"
    os.makedirs(output_dir, exist_ok=True)
    os.chdir(output_dir)
    name = parameters["output"]
    mac = template.safe_substitute(parameters)
    mac_name = name + ".mac"
    with open(mac_name, "w") as fout:
        fout.write(mac)
    command = "../build/pi-decay"
    p = subprocess.Popen(command + " " + mac_name, shell=True,
                         stdout=subprocess.PIPE,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         encoding='utf-8')
    out, err = p.communicate()
    with open(name + ".log", "w") as fout:
        fout.write(out)
        fout.write(err)
    p.wait()
    os.chdir(pwd)
    return name


def main():
    with Pool()as p:
        for data in p.imap_unordered(run, generator()):
            print(data)
    return 0


if __name__ == '__main__':
    main()
