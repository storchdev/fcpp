# Deploy

Pushing to `main` runs `.github/workflows/deploy.yml`: it builds the Docker image with `basePath=/fcpp`,
ships it to the VPS over SSH (`docker save | ssh docker load`), and runs it on `127.0.0.1:3100`.
nginx on the VPS proxies `hudsonshi.com/fcpp` to it (`nginx-fcpp.conf`, already applied).

Repo secrets: `VPS_HOST`, `VPS_USER`, `VPS_SSH_KEY` (private key whose public half is in the VPS user's
`~/.ssh/authorized_keys`; that user must be in the `docker` group).
