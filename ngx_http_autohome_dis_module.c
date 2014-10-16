#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <sys/types.h>
#include <image_data_block.h>

/* Module config */
typedef struct {
	ngx_str_t ed;	
} ngx_http_autohome_dis_loc_conf_t;

extern void nginx_module_invoke_url_parser(empty_struct * p, char * src_fullpath, char * des_fullpath, image_data_t * retval);
empty_struct p;

static char *ngx_http_autohome_dis(ngx_conf_t *cf, ngx_command_t *cmd, void *conf); 
static void *ngx_http_autohome_dis_create_loc_conf(ngx_conf_t *cf); 
static char *ngx_http_autohome_dis_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child); 

/* Directives */
static ngx_command_t ngx_http_autohome_dis_commands[] = {
	{ 	ngx_string("autohome_dis_recommend"),       
		NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,       
		ngx_http_autohome_dis,       
		NGX_HTTP_LOC_CONF_OFFSET,       
		offsetof(ngx_http_autohome_dis_loc_conf_t, ed),       
		NULL },         
		
		ngx_null_command 
}; 

/* Http context of the module */
static ngx_http_module_t ngx_http_autohome_dis_module_ctx = {     
	NULL,                                  /* preconfiguration */    
	NULL,                                  /* postconfiguration */      
	
	NULL,                                  /* create main configuration */    
	NULL,                                  /* init main configuration */      
	
	NULL,                                  /* create server configuration */    
	NULL,                                  /* merge server configuration */      
	
	ngx_http_autohome_dis_create_loc_conf,         /* create location configration */    
	ngx_http_autohome_dis_merge_loc_conf           /* merge location configration */
}; 


/* Module */
ngx_module_t ngx_http_autohome_dis_module = {     
	NGX_MODULE_V1,     
	&ngx_http_autohome_dis_module_ctx,             /* module context */    
	ngx_http_autohome_dis_commands,                /* module directives */    
	NGX_HTTP_MODULE,                       /* module type */    
	NULL,                                  /* init master */    
	NULL,                                  /* init module */    
	NULL,                                  /* init process */    
	NULL,                                  /* init thread */    
	NULL,                                  /* exit thread */    
	NULL,                                  /* exit process */    
	NULL,                                  /* exit master */    
	NGX_MODULE_V1_PADDING
}; 

/* Handler function */
static ngx_int_t ngx_http_autohome_dis_handler(ngx_http_request_t *r) {     
	ngx_int_t rc;     
	ngx_buf_t *b;     
	ngx_chain_t out;
	
	ngx_http_autohome_dis_loc_conf_t *elcf;     
	elcf = ngx_http_get_module_loc_conf(r, ngx_http_autohome_dis_module);       
	
	if(!(r->method & (NGX_HTTP_HEAD|NGX_HTTP_GET|NGX_HTTP_POST))){
		return NGX_HTTP_NOT_ALLOWED;
	}
	
	//get URL param key
	ngx_str_t source;
	ngx_http_arg(r, (u_char *) "source", 6, &source);
	if (source.len == 0) {
			return NGX_HTTP_NOT_ALLOWED;
	}
	u_char* source_path;
    source_path=(u_char* )malloc((source.len+1)*sizeof(u_char));
    memset(source_path,0,sizeof(u_char)*(source.len+1));
    ngx_sprintf(source_path,"%V", &source);
	
	
	//get URL param key
	ngx_str_t target;
	ngx_http_arg(r, (u_char *) "target", 6, &target);
	if (target.len == 0) {
			return NGX_HTTP_NOT_ALLOWED;
	}
	u_char* target_path;
    target_path=(u_char* )malloc((target.len+1)*sizeof(u_char));
    memset(target_path,0,sizeof(u_char)*(target.len+1));
    ngx_sprintf(target_path,"%V", &target);

	r->headers_out.content_type.len = sizeof("text/html") - 1;
	r->headers_out.content_type.data =  (u_char *) "text/html";		
	
	// process image begin
	image_data_t retval;
	nginx_module_invoke_url_parser(&p, (char *)source_path, (char *)target_path, &retval);
	if(retval.code !=NGX_HTTP_OK){
		ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, retval.errorInfo);
	}
	if(retval.len == 0 || retval.data == NULL){		
		if(retval.code == NGX_HTTP_NOT_FOUND)	//只返回404文件不存在
		{
			ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "##########image data 's len = 0 or is NULL, statusCode=404\n");
			return retval.code;
		}
		ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "##########image data 's len = 0 or is NULL, statusCode=500\n");
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}
	free(source_path);
	free(target_path);
	
	
	r->headers_out.status = retval.code;
	r->headers_out.content_length_n = retval.len;		//此时图片长度必定大于0
	
	if(r->method == NGX_HTTP_HEAD){         
		rc = ngx_http_send_header(r);		
		if(rc != NGX_OK) {
			return rc;         
		}     
	}       

	b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));     
	if(b == NULL) {         
		ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "Failed to allocate response buffer.");
		free(retval.data);
		retval.data = NULL;
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}     
	out.buf = b;     
	out.next = NULL;	

	int len = retval.len;
	u_char * ngx_data = ngx_pcalloc(r->pool, len*sizeof(u_char));
	ngx_memcpy(ngx_data, retval.data, len);	
	free(retval.data);			//正常释放opencv数据
	retval.data = NULL;

    b->pos = ngx_data;	
	b->last = ngx_data + len;
	b->memory = 1;
	b->last_buf = 1;
	rc = ngx_http_send_header(r);
	if(rc != NGX_OK){
		return rc;
	}
	
	return ngx_http_output_filter(r, &out);
}

static char *ngx_http_autohome_dis(ngx_conf_t *cf, ngx_command_t *cmd, void *conf) {     
	ngx_http_core_loc_conf_t  *clcf;     
	clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);     
	clcf->handler = ngx_http_autohome_dis_handler;     
	ngx_conf_set_str_slot(cf,cmd,conf);       
	return NGX_CONF_OK; 
}

static void *ngx_http_autohome_dis_create_loc_conf(ngx_conf_t *cf) {     
	ngx_http_autohome_dis_loc_conf_t  *conf;       
	conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_autohome_dis_loc_conf_t));     
	if (conf == NULL) {         
		return NGX_CONF_ERROR;     
	}     
	conf->ed.len = 0;     
	conf->ed.data = NULL;       
	return conf; 
}   

static char *ngx_http_autohome_dis_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child) {     
	ngx_http_autohome_dis_loc_conf_t *prev = parent;     
	ngx_http_autohome_dis_loc_conf_t *conf = child;       
	ngx_conf_merge_str_value(conf->ed, prev->ed, "");       
	return NGX_CONF_OK; 
} 
