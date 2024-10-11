# Rendering Pipelines

## Description

This pull request introduces a rendering pipeline abstraction to the project. The new abstraction aims to decouple the rendering logic from the core application logic, making it easier to extend and maintain the rendering process.

## Motivation

The primary motivation for this change is to improve the modularity and flexibility of the rendering system. By abstracting the rendering pipeline, we can more easily swap out different rendering strategies without affecting the rest of the application.

The strategies themselves can either be sourced from **Script** code (e.g. **GDScript**, **C#**, etc), via **GDExtension** (e.g. **Rust**, **Swift**, etc), or via new **engine modules**. It's a decoupling of core rendering steps from the process that instruments it. 

This concept is very similar to the `ScriptableRenderPipeline` idea that Unity uses, in that it allows user-customization of the rendering engine.

It's implemented with the following ideas:

* A `RenderPipeline` resource, which is a user-definable object (with properties) that can live in the project, or on a particular `SubViewport`.
* A `RenderCommandQueue` object, which abstracts over the normal rendering operations performed by the `RenderingServer`.

Furthermore, the existing rendering backends are refactored to honor this new model.

Two new mechanisms
* Delegation
* Replacement

## Changes

- Added `RenderCommandQueue` object which presents a simplified interface to the rendering server operations.
- Added `RenderPipeline` resource to define the contract for rendering pipelines.
- Added `MultiPassRenderPipeline` which adds support for multiple render passes via the `RenderPass` resource.
- Added `RenderGraph` resource to allow construction of `RenderPipeline`s via a visual editor.

- Refactored existing rendering code to use the new `RenderPipeline` interface
  - This is achieved by wrapping over the `RendererViewport` via the `RenderingServerDefault::_draw` method.

## Testing

- Verified that a simple 2d and 3d application renders correctly using a non-defined `RenderPipeline` (which delegates to the existing rendering subsystem)
- Verified that a simple 2d and 3d application renders correctly when using a minimaly-defined `RenderPipeline` that instructs.

## Related Issues

- TODO

## Checklist

- [ ] Code follows the project's coding standards.
- [ ] Tests have been added/updated as necessary.
- [ ] Documentation has been updated to reflect the changes.
- [ ] All new and existing tests pass.
- [ ] An example project is published and provided.

## Remaining Work

- [ ] Extract `RenderViewport` into pieces via the `RenderPipeline` interface.
- [ ] Delegate to the `RenderPipeline` from the `RendererViewport` for all rendering operations.
- [ ] Get a basic example project up and running.
- [ ] Allow specifying a `RenderPipeline` on a per-project basis.
- [ ] Allow specifying a `RenderPipeline` on a per-viewport basis.

## Sneak Peak

- TODO: Add user-definable render graph preview.
- TODO: Add radiance cascades demo using the new pipeline.