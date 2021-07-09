set -x

# Get this scripts file name
script=`basename "$0"`

# Parse arguments
if [ "$#" -ne 2 ]; then
    echo "${script} USAGE:"
    echo "./${script} env_alias environment_name"
    echo "    env_alias: module provided activate alias, e.g. sv3{r,b,d}"
    echo "    environment_name: corresponding environment name, e.g. release, beta, develop"
    echo "THIS SCRIPT IS NOT INTENDED FOR DIRECT USE. IT IS USED BY THE CI/CD BASH SCRIPTS."
    exit 1
fi

# Activate W-13 Python environment
case $(hostname) in
    sstelmo.lanl.gov|mayhem.lanl.gov)
        projects="/projects"
        module load python/2020.07-python-3.8
        ${env_alias}
        export PATH=$PATH:/apps/abaqus/Commands/
        ;;  # No fall through
    sn-fey?.lanl.gov|sn-rfe?.lanl.gov|sn???.lanl.gov)
        module load python/3.8-anaconda-2020.07
        source activate /usr/projects/ea/python/${environment}
        export PATH=$PATH:/usr/projects/ea/abaqus/Commands/
        ;;
    *)
        echo "Unknown or unsupported host $(hostname)."
        exit 2
esac
