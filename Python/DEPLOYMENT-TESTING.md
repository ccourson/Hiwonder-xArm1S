# Deployment Testing Guide for PyPI

This guide explains how to test the deployment of your package to PyPI without actually deploying it to the production PyPI repository. By using TestPyPI, a separate testing environment, you can ensure your package is properly configured before going live.

---

## Step 1: Create an Account on TestPyPI
1. Visit [TestPyPI](https://test.pypi.org/account/register/) and create an account.
2. Verify your email address to activate the account.

---

## Step 2: Install Necessary Tools
Ensure you have the required Python tools installed:

```bash
pip install --upgrade build twine
```

---

## Step 3: Build the Package
From the root directory of your project (where `setup.py` or `pyproject.toml` is located), run the following command to build your package:

```bash
python -m build
```

This will create a `dist/` directory containing:
- A source distribution (`.tar.gz`)
- A wheel distribution (`.whl`)

---

## Step 4: Upload to TestPyPI
Use `twine` to upload the package to TestPyPI:

```bash
python -m twine upload --repository testpypi dist/*
```

- When prompted, enter your TestPyPI username and password.
- If you encounter issues, ensure your credentials are correct and your account is verified.

---

## Step 5: Verify on TestPyPI
1. Navigate to your package’s page on TestPyPI:
   - The URL will be: `https://test.pypi.org/project/<package-name>/`
   - For example: `https://test.pypi.org/project/hiwonder-xarm1s-servo-controller/`

2. Confirm that all metadata, descriptions, and files are displayed correctly.

---

## Step 6: Test Installation from TestPyPI
Install your package from TestPyPI to verify it works as expected:

```bash
pip install --index-url https://test.pypi.org/simple/ --no-deps <package-name>
```

- Replace `<package-name>` with your actual package name.
- Use `--no-deps` to skip dependencies unless they are also uploaded to TestPyPI.
- Ensure the package installs and functions correctly.

---

## Step 7: Cleanup
Once testing is complete:
1. Fix any issues identified during the testing process.
2. Optionally delete the package from TestPyPI if it’s no longer needed.

---

## Step 8: Deploy to Production PyPI
After validating your package on TestPyPI, deploy it to the production PyPI repository:

```bash
python -m twine upload dist/*
```

- Use your production PyPI credentials when prompted.
- Verify the package on PyPI: `https://pypi.org/project/<package-name>/`

---

This process ensures your package is properly configured and ready for distribution. Happy deploying! 😊

