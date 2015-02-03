#!/usr/bin/env python
from autogen.autogen import autogen

project = "KDiagram"
version = "2.6.0"
subprojects = ["KChart", "KGantt"]
prefixed = True

autogen(project, version, subprojects, prefixed, policyVersion = 2)
