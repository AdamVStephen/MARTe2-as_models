# MARTe2-as_models

The MARTe2-as_models repository offers a set of toy models that demonstrate various useful features of the MARTe2 real-time framework.

If using clang based tooling for source code indexing, generate the compile_commands.json via "bear make -f Makefile.linux" from time to time.

## GAMs

| Component | Documentation |
| --------- | ------------- |
| [LorenzAttractor](https://github.com/AdamVStephen/MARTe2-as_models/tree/master/Source/Components/GAMs/LorenzAttractor) | [TBA](TBA)|


## Lorenz-2

Layer in message support for changing the parameters and HTTP hooks to trigger the messages, and EPICS hooks likewise.

## Lorenz-1

Take the basic GAM and add ExportData and implement some HTTP resources to expose this.
