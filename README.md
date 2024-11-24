# Basic CICD

## Overview

This repository contains a solution for the **CI/CD Pipeline Development** task for the *SimpleBashUtils* project. The work focuses on automating build, testing, and deployment processes using **GitLab CI/CD** principles.

### Features:
- **Continuous Integration (CI)**: Building, codestyle testing, and integration testing.
- **Continuous Delivery (CD)**: Deployment to a production-like environment.
- **Bonus**: Notification setup via Telegram bot for pipeline results.

---

## Project Structure

### Task Description

The main goal was to create an automated pipeline for the **cat** and **grep** utilities from the *C2_SimpleBashUtils* project. The pipeline includes:

1. **Building**: Compiling the utilities using a `Makefile`.
2. **Codestyle Check**: Verifying code formatting with `clang-format`.
3. **Integration Testing**: Running comprehensive tests on the compiled utilities.
4. **Deployment**: Transferring compiled artifacts to a production-like environment on a second virtual machine.
5. **Notifications**: Sending pipeline results to a Telegram bot.

### Implementation Details

- **GitLab Runner**: Set up and configured on an Ubuntu Server 22.04 LTS virtual machine.
- **Scripts**: Bash scripts used for deployment and artifact transfer via `ssh` and `scp`.
- **Artifacts**: Build outputs are saved with a 30-day retention policy.
- **Virtual Machines**: Two Ubuntu Server 22.04 LTS machines were used for CI and production-like deployment testing.

---

## Deliverables

1. **Pipeline Configuration**  
   The `.gitlab-ci.yml` file defines all stages and their dependencies. Each stage halts the pipeline if errors are encountered.

2. **Virtual Machine Dumps**  
   Saved images of the virtual machines used for runner setup and deployment testing (not included in the repository).

3. **Report**  
   The `report.md` document provides detailed insights into the development process and pipeline testing outcomes.

4. **Telegram Notifications**  
   Notifications are configured to send success/failure updates for CI/CD stages.

---

## Getting Started

1. Clone this repository.  
2. Set up a GitLab Runner as described in `report.md`.  
3. Adjust the `.gitlab-ci.yml` file and deployment scripts for your environment.  
4. Run the pipeline to experience a fully automated CI/CD workflow!

---
