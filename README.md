
# DevOps Test Service

A simple C++ application used to demonstrate a full CI/CD pipeline.

## Project Structure

- `main.cpp`: Core logic of the application.
- `Dockerfile`: Multi-stage build configuration for optimized images.
- `.github/workflows/ci.yml`: Automated CI pipeline for Docker Hub integration.

## CI/CD Flow

1. Developer pushes code to `main` branch.
2. GitHub Actions triggers the build process.
3. Docker image is built and pushed to Docker Hub automatically.
