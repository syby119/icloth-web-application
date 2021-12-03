#pragma once

#include <cstdint>
#include <glad/glad.h>

namespace gl {
class TextureManager {
function WebGLTextures(extensions, state, properties, capabilities, utils) {
		const MultisampledRenderToTextureExtension = extensions.get('WEBGL_multisampled_render_to_texture');

		bool textureNeedsGenerateMipmaps(texture, supportsMips) {
			return texture.generateMipmaps && supportsMips && texture.minFilter !== NearestFilter && texture.minFilter !== LinearFilter;
		}

		function generateMipmap(target) {
			_gl.generateMipmap(target);
		}

		function getInternalFormat(internalFormatName, glFormat, glType) {
			if (internalFormatName !== null) {
				if (_gl[internalFormatName] !== undefined) return _gl[internalFormatName];
				console.warn('THREE.WebGLRenderer: Attempt to use non-existing WebGL internal format \'' + internalFormatName + '\'');
			}

			let internalFormat = glFormat;

			if (glFormat === _gl.RED) {
				if (glType === _gl.FLOAT) internalFormat = _gl.R32F;
				if (glType === _gl.HALF_FLOAT) internalFormat = _gl.R16F;
				if (glType === _gl.UNSIGNED_BYTE) internalFormat = _gl.R8;
			}

			if (glFormat === _gl.RGB) {
				if (glType === _gl.FLOAT) internalFormat = _gl.RGB32F;
				if (glType === _gl.HALF_FLOAT) internalFormat = _gl.RGB16F;
				if (glType === _gl.UNSIGNED_BYTE) internalFormat = _gl.RGB8;
			}

			if (glFormat === _gl.RGBA) {
				if (glType === _gl.FLOAT) internalFormat = _gl.RGBA32F;
				if (glType === _gl.HALF_FLOAT) internalFormat = _gl.RGBA16F; //if ( glType === _gl.UNSIGNED_BYTE ) internalFormat = ( encoding === sRGBEncoding ) ? _gl.SRGB8_ALPHA8 : _gl.RGBA8;

				if (glType === _gl.UNSIGNED_BYTE) internalFormat = _gl.RGBA8;
			}

			if (internalFormat === _gl.R16F || internalFormat === _gl.R32F || internalFormat === _gl.RGBA16F || internalFormat === _gl.RGBA32F) {
				extensions.get('EXT_color_buffer_float');
			}

			return internalFormat;
		}

		function getMipLevels(texture, image, supportsMips) {
			if (textureNeedsGenerateMipmaps(texture, supportsMips) === true) {
				// generated mipmaps via gl.generateMipmap()
				return Math.log2(Math.max(image.width, image.height)) + 1;
			} else if (texture.mipmaps.length > 0) {
				// user-defined mipmaps
				return texture.mipmaps.length;
			} else {
				// texture without mipmaps (only base level)
				return 1;
			}
		} // Fallback filters for non-power-of-2 textures


		function filterFallback(f) {
			if (f === NearestFilter || f === NearestMipmapNearestFilter || f === NearestMipmapLinearFilter) {
				return _gl.NEAREST;
			}

			return _gl.LINEAR;
		} //


		function onTextureDispose(event) {
			const texture = event.target;
			texture.removeEventListener('dispose', onTextureDispose);
			deallocateTexture(texture);
		}

		function deallocateTexture(texture) {
			const textureProperties = properties.get(texture);
			if (textureProperties.__webglInit === undefined) return;

			_gl.deleteTexture(textureProperties.__webglTexture);

			properties.remove(texture);
		}

		let textureUnits = 0;

		function resetTextureUnits() {
			textureUnits = 0;
		}

		function allocateTextureUnit() {
			const textureUnit = textureUnits;

			if (textureUnit >= maxTextures) {
				console.warn('THREE.WebGLTextures: Trying to use ' + textureUnit + ' texture units while this GPU supports only ' + maxTextures);
			}

			textureUnits += 1;
			return textureUnit;
		} //


		function setTexture2D(texture, slot) {
			const textureProperties = properties.get(texture);

			if (texture.version > 0 && textureProperties.__version !== texture.version) {
				const image = texture.image;
				uploadTexture(textureProperties, texture, slot);
			}

			state.activeTexture(_gl.TEXTURE0 + slot);
			state.bindTexture(_gl.TEXTURE_2D, textureProperties.__webglTexture);
		}

		function setTextureCube(texture, slot) {
			const textureProperties = properties.get(texture);

			if (texture.version > 0 && textureProperties.__version !== texture.version) {
				uploadCubeTexture(textureProperties, texture, slot);
				return;
			}

			state.activeTexture(_gl.TEXTURE0 + slot);
			state.bindTexture(_gl.TEXTURE_CUBE_MAP, textureProperties.__webglTexture);
		}

		const wrappingToGL = {
			[RepeatWrapping]: _gl.REPEAT,
			[ClampToEdgeWrapping]: _gl.CLAMP_TO_EDGE,
			[MirroredRepeatWrapping]: _gl.MIRRORED_REPEAT
		};
		const filterToGL = {
			[NearestFilter]: _gl.NEAREST,
			[NearestMipmapNearestFilter]: _gl.NEAREST_MIPMAP_NEAREST,
			[NearestMipmapLinearFilter]: _gl.NEAREST_MIPMAP_LINEAR,
			[LinearFilter]: _gl.LINEAR,
			[LinearMipmapNearestFilter]: _gl.LINEAR_MIPMAP_NEAREST,
			[LinearMipmapLinearFilter]: _gl.LINEAR_MIPMAP_LINEAR
		};

		function setTextureParameters(textureType, texture, supportsMips) {
			if (supportsMips) {
				_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_S, wrappingToGL[texture.wrapS]);

				_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_T, wrappingToGL[texture.wrapT]);

				if (textureType === _gl.TEXTURE_3D || textureType === _gl.TEXTURE_2D_ARRAY) {
					_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_R, wrappingToGL[texture.wrapR]);
				}

				_gl.texParameteri(textureType, _gl.TEXTURE_MAG_FILTER, filterToGL[texture.magFilter]);

				_gl.texParameteri(textureType, _gl.TEXTURE_MIN_FILTER, filterToGL[texture.minFilter]);
			} else {
				_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_S, _gl.CLAMP_TO_EDGE);

				_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_T, _gl.CLAMP_TO_EDGE);

				if (textureType === _gl.TEXTURE_3D || textureType === _gl.TEXTURE_2D_ARRAY) {
					_gl.texParameteri(textureType, _gl.TEXTURE_WRAP_R, _gl.CLAMP_TO_EDGE);
				}

				if (texture.wrapS !== ClampToEdgeWrapping || texture.wrapT !== ClampToEdgeWrapping) {
					console.warn('THREE.WebGLRenderer: Texture is not power of two. Texture.wrapS and Texture.wrapT should be set to THREE.ClampToEdgeWrapping.');
				}

				_gl.texParameteri(textureType, _gl.TEXTURE_MAG_FILTER, filterFallback(texture.magFilter));

				_gl.texParameteri(textureType, _gl.TEXTURE_MIN_FILTER, filterFallback(texture.minFilter));

				if (texture.minFilter !== NearestFilter && texture.minFilter !== LinearFilter) {
					console.warn('THREE.WebGLRenderer: Texture is not power of two. Texture.minFilter should be set to THREE.NearestFilter or THREE.LinearFilter.');
				}
			}

			if (extensions.has('EXT_texture_filter_anisotropic') === true) {
				const extension = extensions.get('EXT_texture_filter_anisotropic');
				if (texture.type === FloatType && extensions.has('OES_texture_float_linear') === false) return; // verify extension for WebGL 1 and WebGL 2

				if (texture.anisotropy > 1 || properties.get(texture).__currentAnisotropy) {
					_gl.texParameterf(textureType, extension.TEXTURE_MAX_ANISOTROPY_EXT, Math.min(texture.anisotropy, capabilities.getMaxAnisotropy()));

					properties.get(texture).__currentAnisotropy = texture.anisotropy;
				}
			}
		}

		function initTexture(textureProperties, texture) {
			if (textureProperties.__webglInit === undefined) {
				textureProperties.__webglInit = true;
				texture.addEventListener('dispose', onTextureDispose);
				textureProperties.__webglTexture = _gl.createTexture();
			}
		}

		function uploadTexture(textureProperties, texture, slot) {
			let textureType = _gl.TEXTURE_2D;
			if (texture.isDataTexture2DArray) textureType = _gl.TEXTURE_2D_ARRAY;
			if (texture.isDataTexture3D) textureType = _gl.TEXTURE_3D;
			initTexture(textureProperties, texture);
			state.activeTexture(_gl.TEXTURE0 + slot);
			state.bindTexture(textureType, textureProperties.__webglTexture);

			_gl.pixelStorei(_gl.UNPACK_FLIP_Y_WEBGL, texture.flipY);

			_gl.pixelStorei(_gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, texture.premultiplyAlpha);

			_gl.pixelStorei(_gl.UNPACK_ALIGNMENT, texture.unpackAlignment);

			_gl.pixelStorei(_gl.UNPACK_COLORSPACE_CONVERSION_WEBGL, _gl.NONE);

			const image = texture.image;
            glFormat = utils.convert(texture.format);
			let glType = utils.convert(texture.type),
			glInternalFormat = getInternalFormat(texture.internalFormat, glFormat, glType, texture.encoding);
			setTextureParameters(textureType, texture, true);
			let mipmap;
			const mipmaps = texture.mipmaps;

            // regular Texture (image, video, canvas)
            // use manually created mipmaps if available
            // if there are no manual mipmaps
            // set 0 level mipmap and then use GL to generate other mipmap levels
            const levels = getMipLevels(texture, image, supportsMips);
            const useTexStorage = isWebGL2 && texture.isVideoTexture !== true;
            const allocateMemory = textureProperties.__version === undefined;

            if (mipmaps.length > 0 && supportsMips) {
                if (useTexStorage && allocateMemory) {
                    state.texStorage2D(_gl.TEXTURE_2D, levels, glInternalFormat, mipmaps[0].width, mipmaps[0].height);
                }

                for (let i = 0, il = mipmaps.length; i < il; i++) {
                    mipmap = mipmaps[i];

                    if (useTexStorage) {
                        state.texSubImage2D(_gl.TEXTURE_2D, i, 0, 0, glFormat, glType, mipmap);
                    } else {
                        state.texImage2D(_gl.TEXTURE_2D, i, glInternalFormat, glFormat, glType, mipmap);
                    }
                }

                texture.generateMipmaps = false;
            } else {
                if (useTexStorage) {
                    if (allocateMemory) {
                        state.texStorage2D(_gl.TEXTURE_2D, levels, glInternalFormat, image.width, image.height);
                    }

                    state.texSubImage2D(_gl.TEXTURE_2D, 0, 0, 0, glFormat, glType, image);
                } else {
                    state.texImage2D(_gl.TEXTURE_2D, 0, glInternalFormat, glFormat, glType, image);
                }
            }

			if (textureNeedsGenerateMipmaps(texture, supportsMips)) {
				generateMipmap(textureType);
			}

			textureProperties.__version = texture.version;
			if (texture.onUpdate) texture.onUpdate(texture);
		}

		function uploadCubeTexture(textureProperties, texture, slot) {
			if (texture.image.length !== 6) return;
			initTexture(textureProperties, texture);
			state.activeTexture(_gl.TEXTURE0 + slot);
			state.bindTexture(_gl.TEXTURE_CUBE_MAP, textureProperties.__webglTexture);

			_gl.pixelStorei(_gl.UNPACK_FLIP_Y_WEBGL, texture.flipY);

			_gl.pixelStorei(_gl.UNPACK_PREMULTIPLY_ALPHA_WEBGL, texture.premultiplyAlpha);

			_gl.pixelStorei(_gl.UNPACK_ALIGNMENT, texture.unpackAlignment);

			_gl.pixelStorei(_gl.UNPACK_COLORSPACE_CONVERSION_WEBGL, _gl.NONE);

			const cubeImage = [];

			for (let i = 0; i < 6; i++) {
                cubeImage[i] = texture.image[i];
			}

			const image = cubeImage[0],
            glFormat = utils.convert(texture.format),
            glType = utils.convert(texture.type),
            glInternalFormat = getInternalFormat(texture.internalFormat, glFormat, glType, texture.encoding);
			setTextureParameters(_gl.TEXTURE_CUBE_MAP, texture, true);
			let mipmaps;

            mipmaps = texture.mipmaps;

            for (let i = 0; i < 6; i++) {
                state.texImage2D(_gl.TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, glInternalFormat, glFormat, glType, cubeImage[i]);

                for (let j = 0; j < mipmaps.length; j++) {
                    const mipmap = mipmaps[j];
                    state.texImage2D(_gl.TEXTURE_CUBE_MAP_POSITIVE_X + i, j + 1, glInternalFormat, glFormat, glType, mipmap.image[i]);
                }
            }

			if (textureNeedsGenerateMipmaps(texture, supportsMips)) {
				// We assume images for cube map have the same size.
				generateMipmap(_gl.TEXTURE_CUBE_MAP);
			}

			textureProperties.__version = texture.version;
			if (texture.onUpdate) texture.onUpdate(texture);
		} // Render targets
        
		this.allocateTextureUnit = allocateTextureUnit;
		this.resetTextureUnits = resetTextureUnits;
		this.setTexture2D = setTexture2D;
		this.setTextureCube = setTextureCube;
	}
};
}