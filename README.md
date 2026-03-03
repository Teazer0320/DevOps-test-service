
# DevOps Test Service

A simple C++ application used to demonstrate a full CI/CD pipeline.

## Project Structure

- `main.cpp`: Core logic of the application.
- `Dockerfile`: Multi-stage build configuration for optimized images.
- `.github/workflows/ci.yaml`: Automated CI/CD pipeline for Docker Hub and GitOps integration.

## CI/CD Flow

1. Developer pushes code to `main` branch or pushes a version tag.
2. GitHub Actions triggers the build process.
3. Docker image is built and pushed to Docker Hub with appropriate version tag.
4. CI automatically updates the GitOps repository with the new image version.
5. ArgoCD detects the change and deploys to Kubernetes cluster.

## Usage

### Daily Development

For regular development work, simply commit and push to the `main` branch:

```bash
git add .
git commit -m "fix: fixed some bug"
git push
```

→ This will build and push image as `devops-test-service:<commit-sha>` (e.g., `devops-test-service:abc1234`)

### Release a New Version

When you're ready to release a new version, create and push a tag:

```bash
# Create a version tag (use semantic versioning)
git tag v1.0.0

# Push the tag to trigger the release build
git push origin v1.0.0
```

→ This will build and push image as `devops-test-service:v1.0.0`

### Version Tag Format

Use semantic versioning for tags:
- `v1.0.0` - Major release (breaking changes)
- `v1.1.0` - Minor release (new features)
- `v1.0.1` - Patch release (bug fixes)

## Required GitHub Secrets

To enable the full CI/CD pipeline, configure these secrets in your GitHub repository:

- `DOCKER_USERNAME` - Your Docker Hub username
- `DOCKER_PASSWORD` - Your Docker Hub password or access token
- `GITOPS_REPO` - GitOps repository name (e.g., `teazer0/DevOps-test-gitOps`)
- `GITOPS_TOKEN` - GitHub Personal Access Token with repo write permissions
